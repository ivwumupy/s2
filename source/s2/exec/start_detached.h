#pragma once

#include "s2/exec/connect.h"

//
// #include "s2/base/check.h"

//
#include <stdio.h>

namespace s2::exec {
namespace internal {
template <typename Ops> struct start_detached_receiver {
  Ops* ops;
  auto set_value(auto&&...) -> void {
    printf("ops %p deleted\n", (void*)ops);
    delete ops;
    // s2_check(false);
  }
};
template <typename S> struct start_ops {
  using ops_t = connect_result_type<S, start_detached_receiver<start_ops>>;
  template <typename T>
  start_ops(T&& t)
      : ops{base::forward<T>(t).connect(
            start_detached_receiver<start_ops>{this})} {}
  void start() { ops.start(); }
  ops_t ops;
};
} // namespace internal
// `start_detached` is a sender consumer
template <typename S> auto start_detached(S&& s) {
  auto ops = new internal::start_ops<S>{base::forward<S>(s)};
  ops->start();
}
} // namespace s2::exec
