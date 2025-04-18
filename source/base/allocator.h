#pragma once

#include "base/basic_types.h"

namespace s2::base {
class allocator {
public:
  virtual ~allocator() = default;
  virtual void* alloc(sint size) = 0;
  virtual void dealloc(void* ptr) = 0;
};
allocator& default_allocator();
} // namespace s2::base
