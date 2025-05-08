#pragma once

#include "s2/base/basic_types.h"
#include "s2/base/checked_convert.h"

namespace s2::base {
namespace internal {
inline constexpr usize strlen(char const* s) { return __builtin_strlen(s); }
} // namespace internal
class string_view {
public:
  // [NOTE]
  // we cannot provide the following constructor
  //   template <usize N>
  //   constexpr string_view(char const (&str)[N]) : string_view(str, N - 1) {}
  // because there is no guarantee that it is a null-terminated string.

  constexpr string_view(char const* begin, usize length)
      : beg_{begin}, end_{begin + length} {}

  constexpr string_view(char const* s) : string_view(s, internal::strlen(s)) {}

  constexpr auto length() const -> usize {
    return checked_convert<usize>(end_ - beg_);
  }

  constexpr char const* data() const { return beg_; }

  constexpr char const* begin() { return beg_; }
  constexpr char const* end() { return end_; }

private:
  char const* beg_;
  char const* end_;
};
namespace literals {
inline constexpr string_view operator""_sv(char const* begin, usize len) {
  return string_view(begin, len);
}
} // namespace literals
} // namespace s2::base
