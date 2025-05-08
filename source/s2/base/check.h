#pragma once

#include "s2/base/panic.h" // IWYU pragma: keep

#define s2_check(cond)                                                         \
  do {                                                                         \
    if (!(cond)) {                                                             \
      s2_panic("check `" #cond "` fails");                                     \
    }                                                                          \
  } while (0);
