#pragma once

namespace s2::exec {
namespace internal {
struct start {
  template <typename O>
  constexpr auto operator()(O& o) const -> decltype(auto) {
    return o.start();
  }
};
} // namespace internal
inline constexpr internal::start start{};
} // namespace s2::exec
