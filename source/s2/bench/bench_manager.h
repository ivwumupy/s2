#pragma once

namespace s2::bench {
class benchmark_base;
}

namespace s2::bench {
class bench_manager {
public:
  static auto instance() -> bench_manager*;
  auto register_bench(benchmark_base* b) -> void;
};
} // namespace s2::bench
