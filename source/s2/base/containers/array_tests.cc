#include "s2/base/containers/array.h"
#include "s2/test/expects.h"
#include "s2/test/test_case.h"

namespace s2::base::containers {
namespace {
using test::test_case;
test_case basics{[] {
  array<int, 3> x;
  s2_expect_eq(x.length(), 3);
}};
} // namespace
} // namespace s2::base::containers
