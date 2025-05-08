#include "s2/base/string_view.h"
#include "s2/test/expects.h"
#include "s2/test/test.h"

using namespace s2::base;

TEST(length) {
  string_view s{"hello"};
  s2_expect_eq(s.length(), 5);
}

TEST(comptime) {
  constexpr string_view s{"hello"};
  constexpr auto l = s.length();
  static_assert(l == 5);
  s2_expect_eq(s.length(), 5);
}
