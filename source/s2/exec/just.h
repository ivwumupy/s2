#pragma once

#include "s2/base/move.h"

namespace s2::exec {
namespace internal::just {
template <typename R, typename V> struct ops {
  R recv;
  V value;

  auto start() -> void { recv.set_value(base::move(value)); }
};
template <typename V> struct sender {
  V value;
  template <typename R> auto connect(R&& r) && -> ops<R, V> {
    return {base::forward<R>(r), base::move(value)};
  }
};
} // namespace internal::just
// `just` is a sender factory
template <typename V> auto just(V&& v) {
  return internal::just::sender<V>{base::forward<V>(v)};
}
} // namespace s2::exec
