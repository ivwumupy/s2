#pragma once

#include "s2/base/move.h"

namespace s2::exec {
namespace internal::then {
template <typename R, typename F> struct receiver {
  R r;
  F f;
  template <typename V> auto set_value(V&& v) -> void {
    base::move(r).set_value(base::move(f)(base::forward<V>(v)));
  }
};
template <typename S, typename F> struct sender {
  S s;
  F f;
  template <typename R> auto connect(R&& r) && {
    return base::move(s).connect(
        receiver<R, F>{base::forward<R>(r), base::move(f)});
  }
};
} // namespace internal::then
// `then` is a sender adaptor
template <typename S, typename F> auto then(S&& s, F&& f) {
  return internal::then::sender<S, F>{base::forward<S>(s), base::forward<F>(f)};
}
} // namespace s2::exec
