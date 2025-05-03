#pragma once

#include "s2/base/basic_types.h"

namespace s2::platform::macos::dispatch {
struct data_ref {
  void* inner;
};
struct queue_ref {
  void* inner;
};
data_ref create_data(void const* buffer, usize size);
} // namespace s2::platform::macos::dispatch
