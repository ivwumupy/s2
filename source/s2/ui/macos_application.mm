#include "s2/ui/macos_application.h"

//
#include "s2/ui/macos_window.h"

namespace s2::ui {
macos_application::macos_application() {
  app_ = [NSApplication sharedApplication];
  [app_ setActivationPolicy:NSApplicationActivationPolicyRegular];
  ns_delegate_ = [[s2_ns_application_delegate alloc] init];
  app_.delegate = ns_delegate_;
  render_manager_ = base::make_unique<macos_render_manager>();
  text_manager_ = base::make_unique<macos_text_manager>();
}
macos_application::~macos_application() { [ns_delegate_ release]; }
void macos_application::run() { [app_ run]; }
base::unique_ptr<window> macos_application::make_window(usize width,
                                                        usize height) {
  return base::make_unique<macos_window>(width, height);
}
base::unique_ptr<application> make_macos_application() {
  return base::make_unique<macos_application>();
}
} // namespace s2::ui

@implementation s2_ns_application_delegate
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender {
  return YES;
}
@end
