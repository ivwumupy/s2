#include "s2/base/array.h"
#include "s2/base/panic.h"
#include "s2/base/string_view.h"
#include "s2/ui/application.h"
#include "s2/ui/window.h"

//
#include <stdio.h>

namespace s2 {
namespace {
void test_array() {
  base::array<int> xs;
  for (sint i = 0; i < 10; i++) {
    xs.construct_back(i);
  }
  for (auto& x : xs) {
    printf("xs => %d\n", x);
  }
}
} // namespace
} // namespace s2

int main() {
  s2::test_array();

  using namespace s2::base::literals;
  auto app = s2::ui::make_application();
  auto win = app->make_window(500, 500);
  win->set_title();
  app->run();
  s2::base::panic("hello editor"_sv);
  s2::base::array<int> x{1, 2, 3};
  return 0;
}
