#include "base/base.h"

//
#include <stdio.h>

void sb_panic_with_info(char const *msg, char const *file, i32 line) {
  fprintf(stderr,
          "==== PANIC ====\n"
          "message: %s\n"
          "location: %s:%d\n"
          "backtrace:\n",
          msg, file, line);
  sb_print_backtrace();
  __builtin_trap();
}
