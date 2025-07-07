#pragma once

#include "s2/base/panic.h"

#define s2_check(cond)                                                         \
  do {                                                                         \
    if (!(cond)) {                                                             \
      s2_panic_here();                                                         \
    }                                                                          \
  } while (0)
