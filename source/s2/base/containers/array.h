#pragma once

#include "s2/base/basic_types.h"

namespace s2::base::containers {
template <typename T, usize N> struct array {
  constexpr auto length() const noexcept -> usize { return N; }
  T data_[N];
};
template <typename T, typename... U>
array(T, U...) -> array<T, 1 + sizeof...(U)>;
} // namespace s2::base::containers
