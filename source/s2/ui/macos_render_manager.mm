#include "s2/ui/macos_render_manager.h"

//
#include "s2/ui/macos_shaders.h"
#include "s2/ui/macos_window.h"

namespace s2::ui {
namespace internal {
namespace {
struct uniform_data {
  float viewport_size[2];
};
struct triangle_vertex {
  float position[2];
  base::u32 color;
};
} // namespace
} // namespace internal
macos_render_manager::macos_render_manager() {
  device_ = MTLCreateSystemDefaultDevice();
  queue_ = [device_ newCommandQueue];
  init_shaders();
  init_pipelines();
  init_pass_desc();
}
macos_render_manager::~macos_render_manager() {
  [pass_desc_ release];
  [triangle_pipeline_ release];
  [shaders_ release];
  [queue_ release];
  [device_ release];
}
void macos_render_manager::init_shaders() {
  auto shaders_data = dispatch_data_create(
      s2_ui_macos_shaders, s2_ui_macos_shaders_len, dispatch_get_main_queue(),
      DISPATCH_DATA_DESTRUCTOR_DEFAULT);
  NSError* error;
  shaders_ = [device_ newLibraryWithData:shaders_data error:&error];
  dispatch_release(shaders_data);
}
void macos_render_manager::init_pipelines() {
  auto desc = [[MTLRenderPipelineDescriptor alloc] init];
  // triangle pipeline
  auto triangle_vertex = [shaders_ newFunctionWithName:@"triangle_vertex"];
  auto triangle_fragment = [shaders_ newFunctionWithName:@"triangle_fragment"];
  desc.vertexFunction = triangle_vertex;
  desc.fragmentFunction = triangle_fragment;

  auto vert_desc = [MTLVertexDescriptor vertexDescriptor];
  vert_desc.layouts[0].stepFunction = MTLVertexStepFunctionPerVertex;
  vert_desc.layouts[0].stride = 12; // float4 + uint32
  vert_desc.attributes[0].format = MTLVertexFormatFloat2;
  vert_desc.attributes[0].offset = 0;
  vert_desc.attributes[0].bufferIndex = 0;
  vert_desc.attributes[1].format = MTLVertexFormatUChar4;
  vert_desc.attributes[1].offset = 8;
  vert_desc.attributes[1].bufferIndex = 0;
  desc.vertexDescriptor = vert_desc;

  desc.colorAttachments[0].pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;

  NSError* error;
  triangle_pipeline_ = [device_ newRenderPipelineStateWithDescriptor:desc
                                                               error:&error];

  [triangle_vertex release];
  [triangle_fragment release];
  [desc release];
}
void macos_render_manager::init_pass_desc() {
  pass_desc_ = [[MTLRenderPassDescriptor alloc] init];
  pass_desc_.colorAttachments[0].loadAction = MTLLoadActionClear;
  pass_desc_.colorAttachments[0].storeAction = MTLStoreActionStore;
  pass_desc_.colorAttachments[0].clearColor = MTLClearColorMake(0, 1, 1, 1);
}
void macos_render_manager::setup_window(window* w) {
  auto win = static_cast<macos_window*>(w);
  auto layer = win->metal_layer();
  layer.device = device_;
}
void macos_render_manager::render_batch(window* w, draw_batch const& b) {
  auto win = static_cast<macos_window*>(w);

  @autoreleasepool {
    auto cmdbuf = [queue_ commandBuffer];
    auto drawable = win->drawable();
    pass_desc_.colorAttachments[0].texture = drawable.texture;
    auto encoder = [cmdbuf renderCommandEncoderWithDescriptor:pass_desc_];

    static const internal::uniform_data uniform = {1000, 1000};
    static const internal::triangle_vertex vertices[] = {
        {0, 0, 0x00ff0000},    {250, 0, 0x000000ff}, {250, 250, 0x0000ff00},

        {-250, 0, 0xffff0000}, {0, 0, 0xff0000ff},   {0, 250, 0xff00ff00},
    };

    [encoder setRenderPipelineState:triangle_pipeline_];
    [encoder setVertexBytes:&vertices length:sizeof(vertices) atIndex:0];
    [encoder setVertexBytes:&uniform length:sizeof(uniform) atIndex:1];

    [encoder drawPrimitives:MTLPrimitiveTypeTriangle
                vertexStart:0
                vertexCount:6];

    [encoder endEncoding];
    [cmdbuf presentDrawable:drawable];
    [cmdbuf commit];
  }
}
} // namespace s2::ui
