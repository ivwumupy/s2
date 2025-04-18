#include "s2/base/panic.h"

//
#include "s2/base/backtrace.h"
#include "s2/config.h"

//
#include <stdio.h>

#if defined(S2_PLATFORM_MSVC)
#include <stdlib.h>
#endif

namespace s2::base {
void panic(string_view message, source_location loc) {
  fprintf(stderr,
          "====[ PANIC ]====\n"
          "message: %s\n"
          "location: %s:%ld\n"
          "backtrace:\n",
          message.data(), loc.file().data(), loc.line());
  print_backtrace();
#if defined(S2_PLATFORM_CLANG)
  __builtin_trap();
#elif defined(S2_PLATFORM_MSVC)
    exit(1);
#endif
}
} // namespace s2::base
