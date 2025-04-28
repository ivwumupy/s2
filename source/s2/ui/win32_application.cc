#include "s2/ui/win32_application.h"

//
#include "s2/base/panic.h"
#include "s2/ui/window.h"

namespace s2::ui {
base::unique_ptr<application> make_win32_application() {
  return base::make_unique<win32_application>();
}
win32_application::win32_application() {}
win32_application::~win32_application() {}
void win32_application::run() {}
base::unique_ptr<window> win32_application::make_window(usize width,
                                                        usize height) {
  using namespace base::literals;
  base::panic("todo"_sv);
  return nullptr;
}
render_manager* win32_application::get_render_manager() {
  using namespace base::literals;
  base::panic("todo"_sv);
  return nullptr;
}
text_manager* win32_application::get_text_manager() {
  using namespace base::literals;
  base::panic("todo"_sv);
  return nullptr;
}
} // namespace s2::ui
