#pragma once

namespace s2::base::pointers {
template <typename T> class raw_ptr {
public:
  constexpr raw_ptr() = default;
  constexpr raw_ptr(T* ptr) : ptr_{ptr} {}

  constexpr auto operator->() -> T* { return ptr_; }
  constexpr auto operator->() const -> T const* { return ptr_; }

  constexpr auto as_raw() -> T* { return ptr_; }
  constexpr auto as_raw() const -> T const* { return ptr_; }

private:
  T* ptr_ = nullptr;
};
} // namespace s2::base::pointers
