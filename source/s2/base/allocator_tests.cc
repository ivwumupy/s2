#include "s2/base/allocator.h"
#include "s2/test/test_case.h"

#include <stdio.h>

using s2::test::test_case;

namespace {
using namespace s2;
test_case basics{[] {
  constexpr int x = [] {
    constexpr base::v2::default_allocator<int> alloc{};
    int* q = alloc.alloc();
    new (q) int(1);
    *q = 1;
    int r = *q;
    alloc.free(q);
    return r;
  }();
  printf("%d\n", x);
}};
} // namespace
