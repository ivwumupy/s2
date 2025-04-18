#include "s2/base/allocator.h"

//
#include <stdlib.h>

namespace s2::base {
class libc_allocator final : public allocator {
public:
  void* alloc(sint size) override { return ::malloc(size); }
  void dealloc(void* ptr) override { ::free(ptr); }
};
allocator& default_allocator() {
  static libc_allocator instance;
  return instance;
}
} // namespace s2::base
