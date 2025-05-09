#include "s2/test/expects.h"
#include "s2/test/test.h"

TEST(dummy) { s2_expect(1 + 1 == 2); }
TEST(dummy2) { s2_expect(true); }

namespace {
s2::test::test dummy3{[] {}};
void foo() {}
s2::test::test dummy4{foo};
} // namespace
