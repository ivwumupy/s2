#include "s2/base/strings/string.h"
#include "s2/test/expects.h"
#include "s2/test/test_case.h"

namespace s2::base::strings {
namespace {
using s2::test::test_case;
using namespace literals;
test_case basics{[] {
  string s("abc", 3);
  s2_expect_eq(s.length(), 3);
  s2_expect_eq(s, "abc"_s);
}};
} // namespace
} // namespace s2::base::strings
