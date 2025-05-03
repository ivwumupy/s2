#pragma once

namespace std {
template <typename T, typename... Args> struct coroutine_traits {
  using promise_type = T::promise_type;
};

template <typename P = void> class coroutine_handle {
public:
  static constexpr coroutine_handle from_address([[maybe_unused]] void* addr) {
    return {};
  }

  constexpr operator coroutine_handle<>() { return {}; }
};

struct suspend_never {
  constexpr bool await_ready() noexcept { return true; }
  constexpr void await_suspend(coroutine_handle<>) noexcept {}
  constexpr void await_resume() noexcept {}
};
struct suspend_always {
  constexpr bool await_ready() noexcept { return false; }
  constexpr void await_suspend(coroutine_handle<>) noexcept {}
  constexpr void await_resume() noexcept {}
};
} // namespace std

namespace s2::base {
using std::suspend_always;
using std::suspend_never;
using std::coroutine_handle;
} // namespace s2::base
