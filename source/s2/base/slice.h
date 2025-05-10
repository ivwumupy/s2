#pragma once

#include "s2/base/basic_types.h"
#include "s2/base/check.h"
#include "s2/base/checked_convert.h"

namespace s2::base {
template <typename T> class slice {
public:
  slice(T* begin, T* end) : begin_{begin}, end_{end} {}

  auto count() const -> usize { return checked_convert<usize>(end_ - begin_); }

  auto begin() -> T* { return begin_; }
  auto begin() const -> T const* { return begin_; }
  auto end() -> T* { return end_; }
  auto end() const -> T const* { return end_; }

  auto operator[](usize i) -> T& {
    s2_check(begin_ + i < end_);
    return begin_[i];
  }
  auto operator[](usize i) const -> T const& {
    s2_check(begin_ + i < end_);
    return begin_[i];
  }

  auto as_bytes() -> slice<byte> {
    return {reinterpret_cast<byte*>(begin_), reinterpret_cast<byte*>(end_)};
  }

private:
  T* begin_;
  T* end_;
};
} // namespace s2::base
