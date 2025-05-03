#pragma once

#include "s2/base/basic_types.h"
#include "s2/base/inline_array.h"
#include "s2/base/move.h"
#include "s2/base/unreachable.h"

namespace s2::base {
namespace internal {
template <usize N> constexpr usize max_size(inline_array<usize, N> arr) {
  usize value = 0;
  for (usize i = 0; i < N; i++) {
    if (value < arr[i])
      value = arr[i];
  }
  return value;
}
template <typename... Ts> struct alignas(Ts...) variant_storage {
  static constexpr usize storage_size =
      max_size(make_inline_array<usize>(sizeof(Ts)...));

  template <usize I> constexpr auto get_ptr() {
    using T = type_pack_element<I, Ts...>;
    return reinterpret_cast<T*>(buffer);
  }

  byte buffer[storage_size];
};
} // namespace internal
template <typename... Ts>
  requires(sizeof...(Ts) > 0)
class variant {
  using storage_type = internal::variant_storage<Ts...>;
  static constexpr usize type_count = sizeof...(Ts);

public:
  template <typename T> constexpr variant([[maybe_unused]] T&& t) {}

  constexpr variant(variant&& other)
      : storage_{move(other)}, index_{other.index_} {}

  template <typename F> decltype(auto) visit(F&& func) {
    return visit_impl(forward<F>(func));
  }

private:
  template <usize I, typename F>
    requires(I < type_count)
  decltype(auto) visit_impl(F&& func) {
    if (index_ == I)
      return forward<F>(func)(*storage_.template get_ptr<I>());
    if constexpr (I + 1 < type_count)
      return visit_impl<I + 1, F>(forward<F>(func));
    unreachable();
  }

  storage_type storage_;
  usize index_;
};
} // namespace s2::base
