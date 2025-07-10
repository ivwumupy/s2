#pragma once

namespace s2::base {
template <typename T> struct default_allocator {
  // allocate uninitialized storage for an object of type T
  [[nodiscard]] auto allocate() -> T* {
    // use __builtin_operator_new so that more optimizations are allowed, for
    // example removing paired new/delete
    return static_cast<T*>(__builtin_operator_new(sizeof(T)));
  }
  auto deallocate(T* p) -> void { __builtin_operator_delete(p); }
};
} // namespace s2::base
