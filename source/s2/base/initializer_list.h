#pragma once

#include "s2/base/basic_types.h"

namespace std {
template <typename T> class initializer_list {
public:
  constexpr initializer_list() : begin_{nullptr}, size_{0} {}

  s2::base::usize count() const { return size_; }

private:
  constexpr initializer_list(T const* b, s2::base::usize s)
      : begin_{b}, size_{s} {}

  T const* begin_;
  s2::base::usize size_;
};
} // namespace std

namespace s2::base {
using std::initializer_list;
}
