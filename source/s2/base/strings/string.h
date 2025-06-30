#pragma once

#include "s2/base/containers/vector.h"

namespace s2::base::strings {
class string {
public:
  string(char const* begin, usize len) {
    bytes_.resize_uninitialized(len);
    __builtin_memcpy(bytes_.data(), begin, len);
  }

  auto length() const -> usize { return bytes_.count(); }

  auto data() const -> u8 const* { return bytes_.data(); }

  friend auto operator==(string const& lhs, string const& rhs) -> bool {
    if (lhs.length() != rhs.length())
      return false;
    return __builtin_memcmp(lhs.data(), rhs.data(), lhs.length()) == 0;
  }

private:
  containers::vector<u8> bytes_;
};
namespace literals {
inline string operator""_s(char const* begin, usize len) {
  return string(begin, len);
}
} // namespace literals
} // namespace s2::base::strings
