#pragma once

namespace s2::base {
template <typename T> class slice {
public:
  slice(T* begin, T* end) : begin_{begin}, end_{end} {}

  auto begin() -> T* { return begin_; }
  auto begin() const -> T const* { return begin_; }
  auto end() -> T* { return end_; }
  auto end() const -> T const* { return end_; }

private:
  T* begin_;
  T* end_;
};
} // namespace s2::base
