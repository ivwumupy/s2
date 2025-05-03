#include "s2/platform/macos/dispatch/dispatch.h"

#include "s2/base/check.h"

extern "C" {
extern struct {
  int dummy;
} _dispatch_main_q;
void* dispatch_data_create(void const* buffer, s2::usize size, void* queue,
                           void* block);
}

namespace s2::platform::macos::dispatch {
data_ref create_data(void const* buffer, usize size) {
  auto ptr = dispatch_data_create(buffer, size, &_dispatch_main_q, nullptr);
  s2_check(ptr);
  return {ptr};
}
} // namespace s2::platform::macos::dispatch
