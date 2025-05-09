#pragma once

#include "s2/base/move.h"

namespace s2::bench {
class benchmark_base {
public:
  virtual auto run() -> void = 0;
};
template <typename T, typename F>
class benchmark final : public benchmark_base {
public:
  template <typename S> benchmark(S&& s) : f_{base::forward<S>(s)} {}
  auto run() -> void override {}

private:
  F f_;
};

template <typename F> benchmark(F&& f) -> benchmark<void, F>;
} // namespace s2::bench
