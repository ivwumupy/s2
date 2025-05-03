#pragma once

#include "s2/base/array.h"
#include "s2/base/move.h"
#include "s2/platform/posix/pthread/cond.h"
#include "s2/platform/posix/pthread/mutex.h"

namespace s2::exec {
class run_loop;
namespace internal {
struct run_loop_task {};
template <typename R> struct run_loop_op_state {
  run_loop* loop;
  R recv;
};
struct run_loop_scheduler {
  struct sender {
    template <typename R>
    auto connect(R&& r) const -> run_loop_op_state<base::remove_reference<R>> {
      return {loop, base::forward<R>(r)};
    }
    run_loop* loop;
  };
  auto schedule() -> sender { return {loop}; }

  run_loop* loop;
};
} // namespace internal
class run_loop {
public:
  run_loop() {
    platform::posix::pthread::mutex::init(mutex_);
    platform::posix::pthread::cond::init(cond_);
  }

  void push(internal::run_loop_task* task) {
    mutex_.lock();
    tasks_.construct_back(task);
    cond_.signal();
    mutex_.unlock();
  }

  internal::run_loop_task* pop() {
    mutex_.lock();
    wait_until(
        [&] { return !tasks_.is_empty() || state_ == state::finishing; });
    internal::run_loop_task* result = nullptr;
    if (!tasks_.is_empty()) {
      result = tasks_[index_];
      index_++;
    }
    mutex_.unlock();
    return result;
  }

private:
  enum state { running, finishing };

  void wait_until(auto&& f) {
    while (!f())
      cond_.wait(mutex_);
  }

  state state_;
  platform::posix::pthread::mutex mutex_;
  platform::posix::pthread::cond cond_;
  base::array<internal::run_loop_task*> tasks_;
  // next task index (temp hack)
  usize index_ = 0;
};
} // namespace s2::exec
