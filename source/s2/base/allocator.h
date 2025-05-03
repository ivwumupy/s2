#pragma once

#include "s2/base/basic_types.h"

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
template <typename T> struct default_allocator {};
} // namespace v2
} // namespace s2::base
