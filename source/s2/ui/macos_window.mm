#include "s2/ui/macos_window.h"

//
#include "s2/base/check.h"
#include "s2/ui/window_delegate.h"

namespace s2::ui {
macos_window::macos_window(sint width, sint height)
    : width_{static_cast<float>(width)}, height_{static_cast<float>(height)} {
  init_window();
  init_layer();
  init_view();
}
macos_window::~macos_window() {
  [ns_view_ release];
  [ns_delegate_ release];
  [window_ release];
}
void macos_window::init_window() {
  NSScreen* screen = [NSScreen mainScreen];

  NSWindowStyleMask style =
      NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable |
      NSWindowStyleMaskResizable | NSWindowStyleMaskTitled;

  NSRect rect = NSMakeRect(0, 0, width_, height_);
  // center the window
  rect.origin.x = (screen.frame.size.width - width_) / 2;
  rect.origin.y = (screen.frame.size.height - height_) / 2;

  window_ = [[NSWindow alloc] initWithContentRect:rect
                                        styleMask:style
                                          backing:NSBackingStoreBuffered
                                            defer:NO
                                           screen:screen];
  window_.minSize = NSMakeSize(200, 200);
  window_.releasedWhenClosed = false;

  ns_delegate_ = [[s2_ns_window_delegate alloc] initWithBridge:this];
  window_.delegate = ns_delegate_;

  [window_ makeKeyAndOrderFront:nil];
}
void macos_window::init_layer() {
  metal_layer_ = [CAMetalLayer layer];
  // texture writes automatically have a linear->srgb transform.
  metal_layer_.pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
  // TODO
  metal_layer_.drawableSize = CGSizeMake(1000, 1000);
}
void macos_window::init_view() {
  ns_view_ = [[s2_metal_view alloc] initWithBridge:this];
  window_.contentView = ns_view_;

  // We shall use a layer-hosting view.
  //
  // > One must set the `layer` property first and then set `wantsLayer`.
  // > In a layer-hosting view, do not rely on the view for drawing.
  // > Similarly, do not add subviews to a layer-hosting view.
  //
  ns_view_.layer = metal_layer_;
  ns_view_.wantsLayer = true;
}
void macos_window::render() {
  s2_check(drawable_);
  if (delegate())
    delegate()->render();
}
void macos_window::set_title() { [window_ setTitle:@"s2 engine"]; }
void macos_window::request_render() { render(); }
void macos_window::start_animating() {
  if (!animating_) {
    display_link_.paused = false;
  }
  animating_ = true;
}
void macos_window::stop_animating() {
  if (animating_) {
    display_link_.paused = true;
  }
  animating_ = false;
}
void macos_window::ns_windowWillClose(NSNotification* notification) {
  if (delegate())
    delegate()->will_close();
}
bool macos_window::ns_windowShouldClose(NSWindow* sender) {
  s2_check(sender == window_);
  if (delegate())
    return delegate()->should_close();
  return true;
}
void macos_window::ns_render(CADisplayLink* sender) {
  s2_check(false);
  // s2_check(sender == display_link_);
  // if (delegate())
  //   delegate()->render();
}
void macos_window::ns_viewDidMoveToWindow() {
  s2_check(ns_view_.window == window_);
  setup_display_link();
}
void macos_window::ns_viewDidChangeBackingProperties() { resize_drawable(); }
void macos_window::ns_setFrameSize(NSSize newSize) { resize_drawable(); }
void macos_window::ns_setBoundsSize(NSSize newSize) { resize_drawable(); }
void macos_window::ca_metalDisplayLink_needsUpdate(
    CAMetalDisplayLink* link, CAMetalDisplayLinkUpdate* update) {
  s2_check(link == display_link_);
  drawable_ = update.drawable;
  if (delegate())
    delegate()->render();
}
void macos_window::setup_display_link() {
  if (display_link_) {
    [display_link_ invalidate];
    [display_link_ release];
  }
  display_link_ = [[CAMetalDisplayLink alloc] initWithMetalLayer:metal_layer_];
  // display_link_ = [window_ displayLinkWithTarget:ns_delegate_
  //                                       selector:@selector(render:)];
  display_link_.preferredFrameRateRange =
      CAFrameRateRangeMake(30.0, 60.0, 60.0);
  display_link_.preferredFrameLatency = 2.0;
  display_link_.paused = true;
  display_link_.delegate = ns_view_;
  [display_link_ addToRunLoop:[NSRunLoop mainRunLoop]
                      forMode:NSRunLoopCommonModes];
}
void macos_window::resize_drawable() {
  auto scale = window_.backingScaleFactor;
  CGSize new_size = CGSizeMake(width_ * scale, height_ * scale);
  if (new_size.width <= 0 || new_size.height >= 0)
    return;
  if (new_size.width == metal_layer_.drawableSize.width &&
      new_size.height == metal_layer_.drawableSize.height)
    return;
  metal_layer_.drawableSize = new_size;
}
} // namespace s2::ui

@implementation s2_ns_window_delegate {
  s2::ui::internal::s2_ns_window_delegate_bridge* bridge_;
}
- (instancetype)initWithBridge:
    (s2::ui::internal::s2_ns_window_delegate_bridge*)bridge {
  self = [super init];
  if (self) {
    bridge_ = bridge;
  }
  return self;
}
- (void)windowWillClose:(NSNotification*)notification {
  bridge_->ns_windowWillClose(notification);
}
- (BOOL)windowShouldClose:(NSWindow*)sender {
  return bridge_->ns_windowShouldClose(sender);
}
- (void)render:(CADisplayLink*)sender {
  bridge_->ns_render(sender);
}
@end

@implementation s2_metal_view {
  s2::ui::internal::s2_metal_view_bridge* bridge_;
}
- (instancetype)initWithBridge:(s2::ui::internal::s2_metal_view_bridge*)bridge {
  self = [super init];
  if (self) {
    bridge_ = bridge;
  }
  return self;
}
- (void)mouseMoved:(NSEvent*)event {
}
- (void)mouseDown:(NSEvent*)event {
}
- (void)viewDidMoveToWindow {
  [super viewDidMoveToWindow];
  bridge_->ns_viewDidMoveToWindow();
}
// Override all methods that indicate the view's size has changed.
- (void)viewDidChangeBackingProperties {
  [super viewDidChangeBackingProperties];
  bridge_->ns_viewDidChangeBackingProperties();
}
- (void)setFrameSize:(NSSize)newSize {
  [super setFrameSize:newSize];
  bridge_->ns_setFrameSize(newSize);
}
- (void)setBoundsSize:(NSSize)newSize {
  [super setBoundsSize:newSize];
  bridge_->ns_setBoundsSize(newSize);
}
// CAMetalDisplayLink
- (void)metalDisplayLink:(CAMetalDisplayLink*)link
             needsUpdate:(CAMetalDisplayLinkUpdate*)update {
  bridge_->ca_metalDisplayLink_needsUpdate(link, update);
}

@end
