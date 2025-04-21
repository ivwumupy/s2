#pragma once

#include "s2/base/move.h"

namespace s2::base {
namespace customizations {
template <typename T> constexpr void swap(T& lhs, T& rhs) {
  T tmp = base::move(lhs);
  lhs = base::move(rhs);
  rhs = base::move(tmp);
}
} // namespace customizations
// Use this generic swap only in generic situation.
// Otherwise, prefer the `swap_with` member function.
using customizations::swap;
} // namespace s2::base
