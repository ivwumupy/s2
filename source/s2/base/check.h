#pragma once

#include "s2/base/panic.h" // IWYU pragma: keep

#define s2_check(cond)                                                         \
  do {                                                                         \
    if (!(cond)) {                                                             \
      using namespace s2::base::literals;                                      \
      s2::base::panic("check `" #cond "` fails"##_sv);                         \
    }                                                                          \
  } while (0);
