#pragma once

namespace s2::base {
namespace internal {
template <typename... Ts> struct pure_sender {};
} // namespace internal
template <typename... Ts> constexpr auto pure(Ts&&...) {}

template <typename S> constexpr auto sync_wait() {}
} // namespace s2::base
