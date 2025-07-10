#pragma once

#include "s2/base/move.h"
#include "s2/base/placement_new.h" // IWYU pragma: keep

namespace s2::base {
template <typename T, typename... Args>
constexpr auto construct_at(T* p, Args&&... args) -> T* {
  return new (static_cast<void*>(p)) T(forward<Args>(args)...);
}
} // namespace s2::base
