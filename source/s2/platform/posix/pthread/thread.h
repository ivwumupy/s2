#pragma once

#include "s2/base/pointers/raw_ptr.h"

namespace s2::platform::posix::pthread {
struct thread {
  using routine_type = void* (*)(void*);
  void* inner;
  static int create(
    thread& t, routine_type start, base::pointers::raw_ptr<void> arg);

  int join(base::pointers::raw_ptr<void*> value);
};
} // namespace s2::platform::posix::pthread
