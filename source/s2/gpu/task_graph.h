#pragma once

namespace s2::gpu {
//
class task_graph {
public:
  // Parameters:
  // - `exec`: The task body.
  void add_task(auto&& exec) {}
};
} // namespace s2::gpu
