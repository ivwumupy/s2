#pragma once

#include "s2/base/move.h"
#include "s2/base/tag_invoke.h"

namespace s2::base {
namespace customizations {
template <typename T> constexpr void swap(T& lhs, T& rhs) {
  T tmp = base::move(lhs);
  lhs = base::move(rhs);
  rhs = base::move(tmp);
}
} // namespace customizations
// Use this generic swap only in generic situation.
// Otherwise, prefer the `swap_with` member function.
// using customizations::swap;
namespace swap_ {
struct swap_tag {
  template <typename T>
  constexpr auto operator()(T& lhs, T& rhs) const noexcept -> void {
    tag_invoke(swap_tag{}, lhs, rhs);
  }
};
template <typename T>
constexpr auto tag_invoke(swap_tag, T& lhs, T& rhs) noexcept -> void {
  T tmp = base::move(lhs);
  lhs = base::move(rhs);
  rhs = base::move(tmp);
}
} // namespace swap_
inline constexpr swap_::swap_tag swap{};
} // namespace s2::base
