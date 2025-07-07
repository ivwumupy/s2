#pragma once

namespace s2::base {
template <typename T> auto declval() -> __add_rvalue_reference(T) {
  static_assert(false, "declval not allowed in an evaluated context");
}
} // namespace s2::base
