#pragma once

#include "s2/base/move.h"

namespace s2::test {
class test_base {
public:
  test_base();
  virtual auto run() -> void = 0;
};
template <typename F> struct test final : test_base {
  F f;
  template <typename S> test(S&& s) : f{base::forward<S>(s)} {}
  auto run() -> void override { f(); }
};
template <typename F> test(F&&) -> test<F>;
} // namespace s2::test

#define TEST_CLASS_NAME_(name) name##_s2_test_
#define TEST_INSTANCE_NAME_(name) name##_s2_test_instance_

#define TEST(name)                                                             \
  class TEST_CLASS_NAME_(name) : public ::s2::test::test_base {                \
  public:                                                                      \
    auto run() -> void override;                                               \
  };                                                                           \
  static TEST_CLASS_NAME_(name) TEST_INSTANCE_NAME_(name);                     \
  auto TEST_CLASS_NAME_(name)::run() -> void
