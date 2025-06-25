#pragma once

#include "s2/base/basic_types.h"
#include "s2/base/checked_convert.h"

namespace s2::base::strings {
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

  constexpr string_view(char const* begin, char const* end)
      : beg_{begin}, end_{end} {}
  constexpr string_view(char const* begin, usize length)
      : string_view{begin, begin + length} {}
  constexpr string_view(char const* s) : string_view{s, internal::strlen(s)} {}

  constexpr auto length() const -> usize {
    return checked_convert<usize>(end_ - beg_);
  }

  friend constexpr auto operator==(
    string_view const& lhs, string_view const& rhs) -> bool {
    if (lhs.length() != rhs.length())
      return false;
    return __builtin_memcmp(lhs.beg_, rhs.beg_, lhs.length()) == 0;
  }

  constexpr char const* data() const { return beg_; }

  constexpr char const* begin() { return beg_; }
  constexpr char const* begin() const { return beg_; }
  constexpr char const* end() { return end_; }
  constexpr char const* end() const { return end_; }

private:
  char const* beg_;
  char const* end_;
};
namespace literals {
inline constexpr string_view operator""_sv(char const* begin, usize len) {
  return string_view(begin, len);
}
} // namespace literals
} // namespace s2::base::strings
