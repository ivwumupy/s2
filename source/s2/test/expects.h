#pragma once

#include "s2/base/check.h"

#define s2_expect_eq(lhs, rhs) s2_expect((lhs) == (rhs))
#define s2_expect(expr) s2_check(expr)
