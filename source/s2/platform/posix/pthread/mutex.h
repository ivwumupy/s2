#pragma once

#include "s2/config.h"

namespace s2::platform::posix::pthread {
#if defined(S2_PLATFORM_MACOS)
struct mutex {
  long sig;
  char opaque[56];

  static int init(mutex& m);

  int lock();
  int unlock();
};
static_assert(sizeof(mutex) == 64);
static_assert(alignof(mutex) == 8);

#endif
} // namespace s2::platform::posix::pthread
