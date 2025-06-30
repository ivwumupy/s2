#include "s2/base/panic.h"

//
#include "s2/base/backtrace.h"
#include "s2/config.h"

//
#include <stdio.h>

#if defined(S2_PLATFORM_MSVC)
#include <stdlib.h>
#endif

namespace s2::base::internal {
void panic(char const* msg, char const* file, usize line) {
  fprintf(stderr,
    "====[ PANIC ]====\n"
    "message: %s\n"
    "location: %s:%lu\n"
    "backtrace:\n",
    msg, file, line);
  print_backtrace();
#if defined(S2_PLATFORM_CLANG)
  __builtin_trap();
#elif defined(S2_PLATFORM_MSVC)
  __debugbreak();
#endif
}
} // namespace s2::base::internal
