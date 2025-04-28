#pragma once

#include "s2/base/basic_types.h"
#include "s2/base/move.h"

namespace s2::base {
template <typename T, usize N> struct inline_array {
  T data_[N];
  constexpr T& operator[](usize i) { return data_[i]; }
  constexpr T const& operator[](usize i) const { return data_[i]; }
  constexpr T* begin() { return data_; }
  constexpr T const* begin() const { return data_; }
  constexpr T* end() { return data_ + N; }
  constexpr T const* end() const { return data_ + N; }
};
template <typename T, typename... Ts>
constexpr inline_array<T, sizeof...(Ts)> make_inline_array(Ts&&... ts) {
  return inline_array<T, sizeof...(Ts)>{forward<Ts>(ts)...};
}
template <usize N> constexpr inline_array<usize, N> make_integers() {
  inline_array<usize, N> arr{};
  for (usize i = 0; i < N; i++)
    arr[i] = i;
  return arr;
}
} // namespace s2::base
