#pragma once

#include "s2/base/basic_types.h"

namespace s2::base {
class string_view {
public:
  // [NOTE]
  // we cannot provide the following constructor
  //   template <sint N>
  //   constexpr string_view(char const (&str)[N]) : string_view(str, N - 1) {}
  // because there is no guarantee that it is a null-terminated string.

  constexpr string_view(char const* begin, sint length)
      : beg_{begin}, end_{begin + length} {}

  constexpr char const* data() const { return beg_; }

private:
  char const* beg_;
  char const* end_;
};
namespace literals {
inline constexpr string_view operator""_sv(char const* begin,
                                           internal::size_t len) {
  return string_view(begin, len);
}
} // namespace literals
} // namespace s2::base
