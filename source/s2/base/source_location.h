#pragma once

#include "s2/base/basic_types.h"
#include "s2/base/string_view.h"

namespace s2::base {
// builtins:
//   const char *__builtin_FILE();
//   unsigned __builtin_LINE();
//   __builtin_strlen
class source_location {
public:
  static consteval source_location current(char const* file_ = __builtin_FILE(),
                                           unsigned line_ = __builtin_LINE()) {
    return source_location(string_view(file_, __builtin_strlen(file_)), line_);
  }

  string_view file() const { return file_; }
  sint line() const { return line_; }

private:
  constexpr source_location(string_view file, sint line)
      : file_{file}, line_{line} {}

  string_view file_;
  sint line_;
};
} // namespace s2::base
