#pragma once

#include "s2/base/vector.h"

namespace s2::test {
class test_base;
}

namespace s2::test {
class test_manager {
public:
  static auto instance() -> test_manager*;

  void register_test(test_base* t) { tests_.construct_back(t); }
  void run_all();

private:
  base::vector<test_base*> tests_;
};
} // namespace s2::test
