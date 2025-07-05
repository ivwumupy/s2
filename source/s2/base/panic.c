#include <stdio.h>

void sb_panic(char const* file, int line) {
  fprintf(stderr,
    "==== panic ====\n"
    "file: %s\n"
    "line: %d\n",
    file, line);
  __builtin_trap();
}
