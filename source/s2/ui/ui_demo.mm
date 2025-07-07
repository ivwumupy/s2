#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
#import <AppKit/AppKit.h>
#include <CoreText/CoreText.h>
#import <Metal/Metal.h>
#import <QuartzCore/QuartzCore.h>
#include <dispatch/dispatch.h>

#include "s2/base/expected.h"
#include "s2/base/panic.h"
#include "s2/ui/shaders.h"

#include <vector>

#define CHECK(cond)                                                            \
  do {                                                                         \
    if (!(cond)) {                                                             \
      sb_panic_here();                                                         \
    }                                                                          \
  } while (0);

@interface AppDelegate : NSObject <NSApplicationDelegate>
@end

@interface WindowDelegate : NSObject <NSWindowDelegate>
@end

@interface MetalView : NSView <CAMetalDisplayLinkDelegate>
@end

struct app_context {
  NSApplication* app;
  NSWindow* win;
  CAMetalLayer* metal_layer;
  CAMetalDisplayLink* display_link;
  id<CAMetalDrawable> drawable;
  float width;
  float height;
  // Metal
  id<MTLDevice> device;
  id<MTLCommandQueue> queue;
  id<MTLLibrary> shaders;
  id<MTLRenderPipelineState> sdf_pipeline;
  id<MTLFunction> sdf_vert;
  id<MTLFunction> sdf_frag;
  MTLRenderPassDescriptor* pass_desc;
  CTFontRef font;
};

void render(struct app_context* ctx);

@implementation AppDelegate
- (bool)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender {
  return true;
}
@end

@implementation WindowDelegate
@end

@implementation MetalView {
  struct app_context* app;
}
- (instancetype)init_with_c:(struct app_context*)c {
  self = [super init];
  if (self) {
    app = c;
  }
  return self;
}
// CAMetalDisplayLinkDelegate
- (void)metalDisplayLink:(CAMetalDisplayLink*)link
             needsUpdate:(CAMetalDisplayLinkUpdate*)update {
  app->drawable = update.drawable;
  render(app);
}
- (void)viewDidMoveToWindow {
  [super viewDidMoveToWindow];
  [self setup_display_link];
}
// Override all methods that indicate the view's size has changed.
- (void)viewDidChangeBackingProperties {
  [super viewDidChangeBackingProperties];
  [self resize_drawable];
}
- (void)setFrameSize:(NSSize)newSize {
  [super setFrameSize:newSize];
  [self resize_drawable];
}
- (void)setBoundsSize:(NSSize)newSize {
  [super setBoundsSize:newSize];
  [self resize_drawable];
}
- (void)resize_drawable {
  double scale = [app->win backingScaleFactor];
  app->width = (float)app->win.contentView.bounds.size.width;
  app->height = (float)app->win.contentView.bounds.size.height;
  // app->height = (float)app->win.frame.size.height;
  CGSize new_size = CGSizeMake(app->width * scale, app->height * scale);
  if (new_size.width <= 0 || new_size.height <= 0)
    return;
  if (new_size.width == app->metal_layer.drawableSize.width &&
      new_size.height == app->metal_layer.drawableSize.height)
    return;
  app->metal_layer.drawableSize = new_size;
}
- (void)setup_display_link {
  if (app->display_link) {
    [app->display_link invalidate];
    [app->display_link release];
  }
  app->display_link =
    [[CAMetalDisplayLink alloc] initWithMetalLayer:app->metal_layer];
  app->display_link.preferredFrameRateRange =
    CAFrameRateRangeMake(30.0, 60.0, 60.0);
  app->display_link.preferredFrameLatency = 2.0;
  app->display_link.paused = false;
  app->display_link.delegate = self;
  [app->display_link addToRunLoop:[NSRunLoop mainRunLoop]
                          forMode:NSRunLoopCommonModes];
  printf("display link added\n");
}
@end

void init_app(struct app_context* ctx) {
  // init NSApplication
  ctx->app = [NSApplication sharedApplication];
  [ctx->app setActivationPolicy:NSApplicationActivationPolicyRegular];
  ctx->win = NULL;
  ctx->app.delegate = [[AppDelegate alloc] init];
  // init NSWindow
  NSScreen* screen = [NSScreen mainScreen];
  NSWindowStyleMask style =
    NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable |
    NSWindowStyleMaskResizable | NSWindowStyleMaskTitled;
  NSRect rect = NSMakeRect(0, 0, ctx->width, ctx->height);
  // center the window
  rect.origin.x = (screen.frame.size.width - ctx->width) / 2;
  rect.origin.y = (screen.frame.size.height - ctx->height) / 2;
  ctx->win = [[NSWindow alloc] initWithContentRect:rect
                                         styleMask:style
                                           backing:NSBackingStoreBuffered
                                             defer:NO
                                            screen:screen];
  ctx->win.minSize = NSMakeSize(200, 200);
  [ctx->win setTitle:@"UI Demo"];
  // init CAMetalLayer
  ctx->metal_layer = [CAMetalLayer layer];
  // texture writes automatically have a linear->srgb transform
  ctx->metal_layer.pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
  // w->metal_layer.drawableSize = CGSizeMake(2 * w->width, 2 * w->height);
  // init NSView
  MetalView* view = [[MetalView alloc] init_with_c:ctx];
  view.layer = ctx->metal_layer;
  view.wantsLayer = true;
  ctx->win.contentView = view;
  // show
  [ctx->win makeKeyAndOrderFront:nil];
}

void init_metal(struct app_context* ctx) {
  NSError* error = NULL;

  // device and queue
  ctx->device = MTLCreateSystemDefaultDevice();
  ctx->queue = [ctx->device newCommandQueue];

  // shader library
  dispatch_data_t shaders_data =
    dispatch_data_create(metal_shaders, sizeof(metal_shaders),
      dispatch_get_main_queue(), DISPATCH_DATA_DESTRUCTOR_DEFAULT);
  ctx->shaders = [ctx->device newLibraryWithData:shaders_data error:&error];
  CHECK(!error);
  dispatch_release(shaders_data);

  // shader functions
  ctx->sdf_vert = [ctx->shaders newFunctionWithName:@"sdf_vert"];
  ctx->sdf_frag = [ctx->shaders newFunctionWithName:@"sdf_frag"];

  // sdf pipeline
  MTLRenderPipelineDescriptor* ppl_desc =
    [[MTLRenderPipelineDescriptor alloc] init];
  ppl_desc.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
  ppl_desc.vertexFunction = ctx->sdf_vert;
  ppl_desc.fragmentFunction = ctx->sdf_frag;
  ctx->sdf_pipeline = [ctx->device newRenderPipelineStateWithDescriptor:ppl_desc
                                                                  error:&error];
  CHECK(!error);

  [ppl_desc release];

  // setup window
  // `metalDisplayLink:needsUpdate` is called only if the metal layer is
  // configured.
  ctx->metal_layer.device = ctx->device;

  // render pass
  ctx->pass_desc = [[MTLRenderPassDescriptor alloc] init];
  ctx->pass_desc.colorAttachments[0].loadAction = MTLLoadActionClear;
  ctx->pass_desc.colorAttachments[0].storeAction = MTLStoreActionStore;
  ctx->pass_desc.colorAttachments[0].clearColor = MTLClearColorMake(0, 1, 1, 1);

  // font
  auto name = CFStringCreateWithCString(
    kCFAllocatorDefault, "Times New Roman", kCFStringEncodingUTF8);
  ctx->font = CTFontCreateWithName(name, 20, nullptr);
  CFRelease(name);
}

struct float2 {
  float x;
  float y;
};

enum {
  CMD_CIRCLE,
  CMD_SEGMENT,
  CMD_RECT,
};

struct scene {
  std::vector<uint8_t> cmds;
  std::vector<float> data;
  void add_circle(float2 center, float radius, uint32_t color) {
    cmds.push_back(CMD_CIRCLE);
    push_data(center);
    push_data(radius);
    push_data(color);
  }
  void add_segment(float2 start, float2 end, uint32_t color) {
    cmds.push_back(CMD_SEGMENT);
    push_data(start);
    push_data(end);
    push_data(color);
  }
  void add_rect(float2 origin, float2 size, uint32_t color) {
    cmds.push_back(CMD_RECT);
    push_data(origin);
    push_data(size);
    push_data(color);
  }

  void push_data(float x) { data.push_back(x); }
  void push_data(float2 p) {
    data.push_back(p.x);
    data.push_back(p.y);
  }
  void push_data(uint32_t c) {
    float x;
    static_assert(sizeof(x) == sizeof(c));
    __builtin_memcpy(&x, &c, sizeof(c));
    data.push_back(x);
  }
};

void render(struct app_context* ctx) {
  id<MTLCommandBuffer> cmdbuf = [ctx->queue commandBuffer];
  ctx->pass_desc.colorAttachments[0].texture = ctx->drawable.texture;
  // CGSize drawable_size = ctx->metal_layer.drawableSize;
  struct {
    // float viewport_size[2];
    uint32_t cmd_count;
  } uniform_data = {
    //{(float)drawable_size.width, (float)drawable_size.height},
    2,
  };
  // printf("size: %.2f, %.2f\n", uniform_data.viewport_size[0],
  //   uniform_data.viewport_size[1]);

  uint8_t cmds[] = {
    CMD_CIRCLE,
    CMD_SEGMENT,
  };
  float data[] = {
    // circle
    100.0, 100.0, // center
    20.0,         // radius
    // segment
    200.0, 100.0, // start
    200.0, 300.0, // end
  };

  id<MTLRenderCommandEncoder> encoder =
    [cmdbuf renderCommandEncoderWithDescriptor:ctx->pass_desc];
  [encoder setRenderPipelineState:ctx->sdf_pipeline];
  [encoder setFragmentBytes:&uniform_data
                     length:sizeof(uniform_data)
                    atIndex:0];
  [encoder setFragmentBytes:cmds length:sizeof(cmds) atIndex:1];
  [encoder setFragmentBytes:data length:sizeof(data) atIndex:2];

  // we use one triangle
  [encoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:0 vertexCount:3];

  [encoder endEncoding];
  [cmdbuf presentDrawable:ctx->drawable];
  [cmdbuf commit];
}

int main(void) {
  struct app_context app;
  memset(&app, 0, sizeof(app));
  app.width = 500;
  app.height = 500;
  init_app(&app);
  init_metal(&app);
  [app.app run];
  s2::base::unexpected x{3};
  s2::base::unexpected y{2};
  y = x;
  return 0;
}
