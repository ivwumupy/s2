#pragma once

#include "s2/base/string_view.h"

namespace s2::base {
// buffered output to stdout
//
// warning: the buffer is not flushed when panic
//
// the implementation can panic, so we cannot flush the buffer in panic()
class console {
public:
  static auto instance() -> console&;

  console();
  ~console();

  auto write_line(string_view s) -> void {
    write(s.data(), s.length());
    write('\n');
  }

  auto write(char c) -> void;
  auto write(char const* s, usize len) -> void;

  auto flush() -> void;

private:
  auto copy_to_buffer(char const* p, usize len) -> void;
  auto output(char const* p, usize len) -> void;

  char* begin_;
  char* end_;
  char* cur_;
};
} // namespace s2::base
