#pragma once

#include "s2/base/array.h"

namespace s2::base {
class string {
public:
  string(char const* begin, usize len);

private:
  array<u8> bytes_;
};
namespace literals {
inline string operator""_s(char const* begin, usize len) {
  return string(begin, len);
}
} // namespace literals
} // namespace s2::base
