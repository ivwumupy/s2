#pragma once

#include "s2/base/basic_types.h"

inline constexpr auto operator new(s2::usize, void* p) noexcept -> void* {
  return p;
}

namespace std {
template <typename T> struct allocator {
  constexpr auto allocate(s2::usize n) const -> T* {
    return static_cast<T*>(__builtin_operator_new(n * sizeof(T)));
  }
  constexpr auto deallocate(T* p, s2::usize n) const -> void {
    __builtin_operator_delete(p, n * sizeof(T));
  }
};
} // namespace std

namespace s2::base {
class allocator {
public:
  constexpr virtual ~allocator() = default;
  constexpr virtual void* alloc(usize size) = 0;
  constexpr virtual void dealloc(void* ptr) = 0;
};
namespace internal {
allocator* runtime_default_allocator();
class comptime_allocator final : public allocator {
public:
  void* alloc([[maybe_unused]] usize size) override { return nullptr; }
  void dealloc([[maybe_unused]] void* ptr) override {}
};
} // namespace internal
inline constexpr allocator* default_allocator() {
  if consteval {
    return new internal::comptime_allocator;
  } else {
    return internal::runtime_default_allocator();
  }
}
// [NOTES]
// 1. every type carries size and alignment info
namespace v2 {
template <typename T>
concept allocator = true;
template <typename T> struct default_allocator {
  constexpr auto alloc() const -> T* { return std::allocator<T>{}.allocate(1); }
  constexpr auto alloc_n(usize n) const -> T* {
    return std::allocator<T>{}.allocate(n);
  }
  constexpr auto free(T* p) const -> void {
    std::allocator<T>{}.deallocate(p, 1);
  }
  constexpr auto free_n(T* p, usize n) const -> void {
    std::allocator<T>{}.deallocate(p, n);
  }
};
} // namespace v2
} // namespace s2::base
