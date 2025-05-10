#include "s2/base/array.h"
#include "s2/base/checked_convert.h"
#include "s2/test/expects.h"
#include "s2/test/test.h"

using namespace s2::base;
using namespace s2::test;

namespace {
test basics{[] {
  array<int> x;
  s2_expect_eq(x.count(), 0);
}};
test grow{[] {
  array<int> x;
  for (int i = 0; i < 100; i++)
    x.construct_back(i);
  s2_expect_eq(x.count(), 100);
  for (int i = 0; i < 100; i++)
    s2_expect_eq(x[checked_convert<usize>(i)], i);
}};
test make{[] {
  auto x = make_array<int>(1, 2, 3, 4, 5);
  s2_expect_eq(x.count(), 5);
  for (int i = 0; i < 5; i++)
    s2_expect_eq(x[checked_convert<usize>(i)], i + 1);
}};
test pop{[] {
  auto x = make_array<int>(1, 2, 3, 4, 5);
  s2_expect_eq(x.count(), 5);
  x.pop();
  s2_expect_eq(x.count(), 4);
  x.pop();
  s2_expect_eq(x.count(), 3);
  x.pop();
  s2_expect_eq(x.count(), 2);
  x.pop();
  s2_expect_eq(x.count(), 1);
  x.pop();
  s2_expect_eq(x.count(), 0);
}};
} // namespace
