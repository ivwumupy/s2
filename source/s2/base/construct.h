#pragma once

#include "s2/base/move.h"
#include "s2/base/placement_new.h" // IWYU pragma: keep

namespace s2::base {
template <typename T, typename... Args>
constexpr T* construct_at(void* ptr, Args&&... args) {
  // `Arg` might be a type in `std` namespace (such as `std::byte` and
  // `std::coroutine_handle`).
  // Therefore it is necessary to avoid ADL.
  return ::new (ptr) T(base::forward<Args>(args)...);
}
template <typename T> constexpr void destruct_at(T* ptr) { ptr->~T(); }
} // namespace s2::base
