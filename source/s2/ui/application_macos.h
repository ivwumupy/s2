#pragma once

#include "s2/base/unique_ptr.h"
#include "s2/ui/application.h"

//
#import <AppKit/AppKit.h>

@interface s2_ns_application_delegate : NSObject <NSApplicationDelegate>
@end

namespace s2::ui {
class macos_application final : public application {
public:
  macos_application();
  ~macos_application();

  void run() override;

  base::unique_ptr<window> make_window(sint width, sint height) override;

private:
  NSApplication* app_;
  s2_ns_application_delegate* ns_delegate_;
};
base::unique_ptr<application> make_macos_application();
} // namespace s2::ui
