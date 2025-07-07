#include <stdio.h>

namespace s2::base {
void panic(char const* file, int line) {
  fprintf(stderr,
    "==== panic ====\n"
    "file: %s\n"
    "line: %d\n",
    file, line);
  __builtin_trap();
}
} // namespace s2::base
