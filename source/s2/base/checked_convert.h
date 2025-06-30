#pragma once

#include "s2/base/check.h"
#include "s2/base/numeric_limits.h"

namespace s2::base {
namespace internal {
template <typename T> inline constexpr bool is_signed = __is_signed(T);
template <typename T> using make_signed = __make_signed(T);
template <typename T> using make_unsigned = __make_unsigned(T);
template <typename T, typename U> constexpr bool safe_less_equal(T t, U u) {
  if constexpr (is_signed<T> == is_signed<U>)
    return t <= u;
  else if constexpr (is_signed<T>)
    return t < 0 ? true : make_unsigned<T>(t) <= u;
  else
    return u < 0 ? false : t <= make_unsigned<U>(u);
}
} // namespace internal
// for numeric types only
template <typename To, typename From> constexpr To checked_convert(From v) {
  check(internal::safe_less_equal(v, numeric_limits<To>::max));
  check(internal::safe_less_equal(numeric_limits<To>::min, v));
  return static_cast<To>(v);
}
} // namespace s2::base
