#pragma once

#include "s2/exec/connect.h"

//
#include "s2/base/check.h"

namespace s2::exec {
namespace internal {
struct start_detached_receiver {
  auto set_value(auto&&...) -> void { s2_check(false); }
};
} // namespace internal
// `start_detached` is a sender consumer
template <typename S> auto start_detached(S&& s) {
  using ops_t = connect_result_type<S, internal::start_detached_receiver>;
  ops_t ops{base::forward<S>(s).connect(internal::start_detached_receiver{})};
  ops.start();
}
} // namespace s2::exec
