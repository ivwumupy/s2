#pragma once

namespace s2::base {
using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long;
using usize = u64;
} // namespace s2::base

namespace s2::base {
template <typename T> struct numeric_limits {
  static constexpr bool is_signed = T(-1) < T(0);
  static constexpr usize digits = static_cast<int>(sizeof(T) * 8 - is_signed);
  static constexpr T min = is_signed ? T(T(1) << digits) : T(0);
  static constexpr T max = is_signed ? T(T(~0) ^ min) : T(~0);
};
} // namespace s2::base

namespace s2 {
using base::usize;
}
