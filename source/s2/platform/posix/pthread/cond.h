#pragma once

#include "s2/config.h"

namespace s2::platform::posix::pthread {
struct mutex;
#if defined(S2_PLATFORM_MACOS)
struct cond {
  long sig;
  char opaque[40];

  static int init(cond& c);
  int signal();
  int wait(mutex& m);
};
static_assert(sizeof(cond) == 48);
static_assert(alignof(cond) == 8);
#endif
} // namespace s2::platform::posix::pthread
