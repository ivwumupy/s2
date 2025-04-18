#include "base/panic.h"

//
#include "base/backtrace.h"

//
#include <stdio.h>

namespace s2::base {
void panic(string_view message, source_location loc) {
  fprintf(stderr,
          "====[ PANIC ]====\n"
          "message: %s\n"
          "location: %s:%ld\n"
          "backtrace:\n",
          message.data(), loc.file().data(), loc.line());
  print_backtrace();
  __builtin_trap();
}
} // namespace s2::base
