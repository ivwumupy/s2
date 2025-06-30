#pragma once

#include "s2/base/basic_types.h"

namespace s2::base {
// Note:
// - `source_location` should have minimal dependencies.
class source_location {
public:
  static consteval source_location current(char const* file_ = __builtin_FILE(),
    unsigned int line_ = __builtin_LINE()) {
    return source_location(file_, line_);
  }

  constexpr auto file() const -> char const* { return file_; }
  constexpr auto line() const -> usize { return line_; }

private:
  constexpr source_location(char const* file, usize line)
      : file_{file}, line_{line} {}

  char const* file_;
  usize line_;
};
} // namespace s2::base
