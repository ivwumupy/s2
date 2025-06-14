#include "s2/test/test_manager.h"

//
#include "s2/test/test_case.h"

//
#include <stdio.h>

namespace s2::test {
auto test_manager::instance() -> test_manager* {
  static test_manager i;
  return &i;
}
auto test_manager::run_all() -> void {
  const usize n = tests_.count();
  for (usize i = 0; i < n; i++) {
    printf("[%lu/%lu]\n", i + 1, n);
    tests_[i]->run();
  }
}
} // namespace s2::test
