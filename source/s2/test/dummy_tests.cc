#include "s2/test/expects.h"
#include "s2/test/test_case.h"

TEST(dummy) { s2_expect(1 + 1 == 2); }
TEST(dummy2) { s2_expect(true); }

namespace {
s2::test::test_case dummy3{[] {}};
void foo() {}
s2::test::test_case dummy4{foo};
} // namespace
