#pragma once

namespace s2::base {
template <typename T> class raw_ptr {
public:
  constexpr raw_ptr() = default;
  constexpr raw_ptr(T* ptr) : ptr_{ptr} {}

  auto operator->(this auto&& self) { return self.ptr_; }
  auto operator*(this auto&& self) { return *self; }

  auto as_raw(this auto&& self) { return self.ptr_; }

private:
  T* ptr_ = nullptr;
};
} // namespace s2::base
