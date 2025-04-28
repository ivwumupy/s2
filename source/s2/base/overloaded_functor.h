#pragma once

namespace s2::base {
template <typename... Ts> struct overloaded_functor : Ts... {
  using Ts::operator()...;
};
} // namespace s2::base
