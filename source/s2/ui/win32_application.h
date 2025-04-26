#pragma once

#include "s2/ui/application.h"

namespace s2::ui {
class win32_application final : public application {
public:
  win32_application();
  ~win32_application();

  void run() override;
  base::unique_ptr<window> make_window(sint width, sint height) override;

  render_manager* get_render_manager() override;
  text_manager* get_text_manager() override;
};
base::unique_ptr<application> make_win32_application();
} // namespace s2::ui