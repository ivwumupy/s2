#pragma once

#include "s2/base/basic_types.h"

namespace s2::base {
template <typename T> struct numeric_limits {
  static constexpr bool is_signed = T(-1) < T(0);
  static constexpr usize digits = static_cast<int>(sizeof(T) * 8 - is_signed);
  static constexpr T min = is_signed ? T(T(1) << digits) : T(0);
  static constexpr T max = is_signed ? T(T(~0) ^ min) : T(~0);
};
} // namespace s2::base
