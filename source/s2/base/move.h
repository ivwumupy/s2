#pragma once

namespace s2::base {
template <typename T> constexpr __remove_reference_t(T)&& move(T&& t) {
  return static_cast<__remove_reference_t(T)&&>(t);
}
template <typename T> constexpr T&& forward(__remove_reference_t(T)& t) {
  return static_cast<T&&>(t);
}

} // namespace s2::base
