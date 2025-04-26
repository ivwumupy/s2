#pragma once

#include "s2/config.h"

namespace s2::base {
#ifdef S2_PLATFORM_CLANG
template <typename T> using remove_reference = __remove_reference_t(T);
template <typename From, typename To>
inline constexpr bool is_convertible = __is_convertible(From, To);
template <typename Derived, typename Base>
inline constexpr bool is_derived_from = __is_base_of(Base, Derived);
#else
namespace internal {
template <typename T> struct remove_reference_impl {
  using type = T;
};
template <typename T> struct remove_reference_impl<T&> {
  using type = T;
};
template <typename T> struct remove_reference_impl<T&&> {
  using type = T;
};
} // namespace internal
template <typename T>
using remove_reference = internal::remove_reference_impl<T>::type;
template <typename From, typename To>
inline constexpr bool is_convertible = __is_convertible_to(From, To);
template <typename Derived, typename Base>
inline constexpr bool is_derived_from = __is_base_of(Base, Derived);
#endif
} // namespace s2::base
