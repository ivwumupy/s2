#pragma once

#include "s2/base/unique_ptr.h"
#include "s2/ui/application.h"
#include "s2/ui/macos_render_manager.h"
#include "s2/ui/macos_text_manager.h"

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

  render_manager* get_render_manager() override {
    return render_manager_.get();
  }

  text_manager* get_text_manager() override { return text_manager_.get(); }

private:
  NSApplication* app_;
  s2_ns_application_delegate* ns_delegate_;
  base::unique_ptr<macos_render_manager> render_manager_;
  base::unique_ptr<macos_text_manager> text_manager_;
};
base::unique_ptr<application> make_macos_application();
} // namespace s2::ui
