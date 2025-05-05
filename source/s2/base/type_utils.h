#pragma once

#include "s2/base/basic_types.h"
#include "s2/config.h"

namespace s2::base {
#ifdef S2_PLATFORM_CLANG
template <typename T> using remove_reference = __remove_reference_t(T);
template <typename T> using add_rvalue_reference = __add_rvalue_reference(T);
template <typename From, typename To>
inline constexpr bool is_convertible = __is_convertible(From, To);
template <typename Derived, typename Base>
inline constexpr bool is_derived_from = __is_base_of(Base, Derived);

template <typename T> using remove_cvref = __remove_cvref(T);

template <usize I, typename... Ts>
using type_pack_element = __type_pack_element<I, Ts...>;

template <typename T> using decay = __decay(T);
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

template <typename T> add_rvalue_reference<T> declval() {
  static_assert(false);
}

} // namespace s2::base
