#include "s2/base/array.h"
#include "s2/ui/application.h"
#include "s2/ui/view.h"
#include "s2/ui/window.h"
#include "s2/ui/window_delegate.h"

//
#include <stdio.h>

namespace s2::editor {
namespace {
class quad : public ui::view {};
class vstack : public ui::view {
public:
  base::array<view*> children_;
};
class padding : public ui::view {
public:
  view* child_;
};
class border : public ui::view {
public:
  view* child_;
};
class delegate : public ui::window_delegate {
public:
  void will_close() override { printf("window is closing\n"); }
  bool should_close() override {
    printf("window should close?\n");
    return true;
  }
};
} // namespace
} // namespace s2::editor

int main() {
  auto app = s2::ui::make_application();
  auto win = app->make_window(500, 500);
  win->set_title();
  s2::editor::delegate d;
  win->set_delegate(&d);
  app->run();
  return 0;
}
