#include "s2/base/strings/string_view.h"
#include "s2/test/expects.h"
#include "s2/test/test_case.h"

namespace s2::base::strings {
namespace {
using s2::test::test_case;
test_case length{[] {
  string_view s{"hello"};
  s2_expect_eq(s.length(), 5);
}};
test_case comptime{[] {
  constexpr string_view s{"hello"};
  constexpr auto l = s.length();
  static_assert(l == 5);
  s2_expect_eq(s.length(), 5);
}};
} // namespace
} // namespace s2::base::strings
