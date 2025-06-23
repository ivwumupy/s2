#include "s2/base/allocator.h"

//
#include <stdlib.h>

namespace s2::base {
namespace v1 {
class libc_allocator final : public allocator {
public:
  void* alloc(usize size) override { return ::malloc(size); }
  void dealloc(void* ptr) override { ::free(ptr); }
};
namespace internal {
allocator* runtime_default_allocator() {
  static libc_allocator instance;
  return &instance;
}
} // namespace internal
} // namespace v1
} // namespace s2::base
