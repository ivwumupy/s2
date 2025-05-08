#pragma once

namespace s2::test {
class test {
public:
  test();
  virtual auto run() -> void = 0;
};
} // namespace s2::test

#define TEST_CLASS_NAME_(name) name##_s2_test_
#define TEST_INSTANCE_NAME_(name) name##_s2_test_instance_

#define TEST(name)                                                             \
  class TEST_CLASS_NAME_(name) : public ::s2::test::test {                     \
  public:                                                                      \
    auto run() -> void override;                                               \
  };                                                                           \
  static TEST_CLASS_NAME_(name) TEST_INSTANCE_NAME_(name);                     \
  auto TEST_CLASS_NAME_(name)::run() -> void
