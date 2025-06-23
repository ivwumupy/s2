#include "s2/base/hash_map.h"
#include "s2/test/test_case.h"

using s2::test::test_case;

namespace {
using namespace s2;
test_case basics{[] { [[maybe_unused]] base::hash_map<int, int> x; }};
} // namespace
