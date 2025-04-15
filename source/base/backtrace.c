#include "base/base.h"

//
#include <stdio.h>
#include <string.h>

//
#include <dlfcn.h>
#include <execinfo.h>

static bool symbolize(void *pc, char *buf, sint size) {
  Dl_info info;
  if (dladdr(pc, &info)) {
    if (strlen(info.dli_sname) < size) {
      strcpy(buf, info.dli_sname);
      return true;
    }
  }
  return false;
}

void sb_print_backtrace() {
  void *entries[128];
  char symbol_buffer[256];
  sint count;
  sint i;
  char const *name;

  count = backtrace(entries, 128);
  for (i = 0; i < count; i++) {
    if (symbolize(entries[i], symbol_buffer, 256)) {
      name = symbol_buffer;
    } else {
      name = "<unknown>";
    }

    printf("  # %p %s\n", entries[i], name);
  }
}
