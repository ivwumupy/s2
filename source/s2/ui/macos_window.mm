#include "s2/ui/macos_window.h"

//
#include "s2/base/check.h"
#include "s2/ui/window_delegate.h"

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

  [window_ makeKeyAndOrderFront:nil];
}
macos_window::~macos_window() {
  [window_ release];
  [ns_delegate_ release];
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
