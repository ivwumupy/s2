#pragma once

#include "s2/base/move.h"

namespace s2::exec {
namespace internal {
struct connect {
  template <typename S, typename R>
  constexpr auto operator()(S&& s, R&& r) const -> decltype(auto) {
    return base::forward<S>(s).connect(base::forward<R>(r));
  }
};
}; // namespace internal
inline constexpr internal::connect connect{};
template <typename S, typename R>
using connect_result_type =
    decltype(connect(base::declval<S>(), base::declval<R>()));
} // namespace s2::exec
