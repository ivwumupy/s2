#pragma once

namespace s2::base {
template <typename T> class raw_ptr {
public:
  constexpr raw_ptr() = default;
  constexpr raw_ptr(T* ptr) : ptr_{ptr} {}

  auto operator->() -> T* { return ptr_; }
  auto operator->() const -> T const* { return ptr_; }

  auto as_raw() -> T* { return ptr_; }
  auto as_raw() const -> T const* { return ptr_; }

private:
  T* ptr_ = nullptr;
};
} // namespace s2::base
