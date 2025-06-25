#pragma once

#include "s2/base/containers/vector.h"

namespace s2::base::strings {
class string {
public:
  string(char const* begin, usize len);

private:
  containers::vector<u8> bytes_;
};
namespace literals {
inline string operator""_s(char const* begin, usize len) {
  return string(begin, len);
}
} // namespace literals
} // namespace s2::base::strings
