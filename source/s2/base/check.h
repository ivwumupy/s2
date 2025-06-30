#pragma once

#include "s2/base/panic.h" // IWYU pragma: keep
#include "s2/base/source_location.h"

#define s2_check(cond)                                                         \
  do {                                                                         \
    if (!(cond)) {                                                             \
      s2_panic("check `" #cond "` fails");                                     \
    }                                                                          \
  } while (0);

namespace s2::base {
inline constexpr auto check(
  bool v, source_location src = source_location::current()) -> void {
  if (!v)
    internal::panic("check failed", src.file(), src.line());
}
} // namespace s2::base
