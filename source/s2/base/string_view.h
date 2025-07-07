#pragma once

#include "s2/base/integers.h"

namespace s2::base {
class string_view {
public:
  constexpr string_view() : data_{nullptr}, length_{0} {}
  constexpr string_view(char const* s) : string_view{s, __builtin_strlen(s)} {}
  constexpr string_view(char const* s, usize len) : data_{s}, length_{len} {}

  constexpr auto length() const -> usize { return length_; }
  constexpr auto data() const -> char const* { return data_; }

  constexpr auto begin() const -> char const* { return data_; }
  constexpr auto end() const -> char const* { return data_ + length_; }

private:
  char const* data_;
  usize length_;
};
} // namespace s2::base
