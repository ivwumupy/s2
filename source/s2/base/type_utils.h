#pragma once

namespace s2::base {
template <typename T> using remove_reference = __remove_reference_t(T);
template <typename From, typename To>
inline constexpr bool is_convertible = __is_convertible(From, To);
} // namespace s2::base
