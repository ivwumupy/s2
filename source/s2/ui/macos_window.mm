#include "s2/ui/macos_window.h"

//
#include "s2/base/check.h"
#include "s2/ui/window_delegate.h"

//
#import <QuartzCore/CoreAnimation.h>

namespace s2::ui {
macos_window::macos_window(sint width, sint height) {
  NSScreen* screen = [NSScreen mainScreen];

  NSWindowStyleMask style =
      NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable |
      NSWindowStyleMaskResizable | NSWindowStyleMaskTitled;

  NSRect rect = NSMakeRect(0, 0, width, height);
  // center the window
  rect.origin.x = (screen.frame.size.width - width) / 2;
  rect.origin.y = (screen.frame.size.height - height) / 2;

  window_ = [[NSWindow alloc] initWithContentRect:rect
                                        styleMask:style
                                          backing:NSBackingStoreBuffered
                                            defer:NO
                                           screen:screen];
  window_.minSize = NSMakeSize(200, 200);
  ns_delegate_ = [[s2_ns_window_delegate alloc] initWithBridge:this];
  window_.delegate = ns_delegate_;
  window_.releasedWhenClosed = false;

  ns_view_ = [[s2_metal_view alloc] initWithBridge:this];
  window_.contentView = ns_view_;

  metal_layer_ = [CAMetalLayer layer];
  // texture writes automatically have a linear->srgb transform.
  metal_layer_.pixelFormat = MTLPixelFormatBGRA8Unorm_sRGB;
  // TODO
  metal_layer_.drawableSize = CGSizeMake(1000, 1000);
  // We shall use a layer-hosting view.
  //
  // > One must set the `layer` property first and then set `wantsLayer`.
  // > In a layer-hosting view, do not rely on the view for drawing.
  // > Similarly, do not add subviews to a layer-hosting view.
  //
  ns_view_.layer = metal_layer_;
  ns_view_.wantsLayer = true;

  [window_ makeKeyAndOrderFront:nil];
}
macos_window::~macos_window() {
  [ns_view_ release];
  [ns_delegate_ release];
  [window_ release];
}
void macos_window::set_title() { [window_ setTitle:@"s2 engine"]; }
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
void macos_window::ns_viewDidChangeBackingProperties() {}
void macos_window::ns_setFrameSize(NSSize newSize) {}
void macos_window::ns_setBoundsSize(NSSize newSize) {}

} // namespace s2::ui

@implementation s2_ns_window_delegate {
  s2::ui::internal::ns_window_bridge* bridge_;
}
- (instancetype)initWithBridge:(s2::ui::internal::ns_window_bridge*)bridge {
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
@end

@implementation s2_metal_view {
  s2::ui::internal::ns_view_bridge* bridge_;
}
- (instancetype)initWithBridge:(s2::ui::internal::ns_view_bridge*)bridge {
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
@end
