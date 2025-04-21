#include "s2/ui/window_macos.h"

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
  [window_ makeKeyAndOrderFront:nil];
}
macos_window::~macos_window() { [window_ release]; }
void macos_window::set_title() { [window_ setTitle:@"s2 engine"]; }
} // namespace s2::ui
