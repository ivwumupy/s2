#pragma once

#include "s2/base/basic_types.h"
#include "s2/base/containers/array.h"
#include "s2/base/strings/string_view.h"

namespace s2::base::strings {
class string;
} // namespace s2::base::strings

namespace s2::base {
class console {
public:
  static auto instance() -> console*;

  // c-str literal
  auto write_line(char const*) -> void {}
  auto write_line(strings::string const& s) -> void {}
  auto write_line(strings::string_view s) -> void {}

  auto write(char c) -> void;

  auto flush() -> void;

  auto reset() -> void { offset_ = 0; }

private:
  static constexpr usize buffer_size = 1024 * 4;

  auto write_impl(byte const* p, usize n) -> void;

  containers::array<byte, buffer_size> buffer_;
  usize offset_ = 0;
};
} // namespace s2::base
