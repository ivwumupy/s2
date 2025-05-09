#pragma once

#include "s2/base/type_utils.h"

namespace s2::base {
template <typename T> constexpr remove_reference<T>&& move(T&& t) {
  using U = remove_reference<T>;
  return static_cast<U&&>(t);
}
template <typename T> constexpr T&& forward(remove_reference<T>& t) {
  return static_cast<T&&>(t);
}
// TODO: When do we need to forward an rvalue?
} // namespace s2::base
