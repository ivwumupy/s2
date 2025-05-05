#pragma once

#include "s2/base/string_view.h"

namespace s2::json {
enum class parse_status {
  success,
  unexpected_eof,
  internal_error,
};
namespace internal {
template <typename It, typename P> struct parser {
  It begin;
  It cur;
  It end;
  P& proxy;

  bool is_end() const { return cur == end; }
  void advance() {
    if (is_end())
      return;
    cur++;
  }
  void skip_whitespace() {
    while (!is_end()) {
      auto c = *cur;
      if (c != ' ' && c != '\n')
        break;
      cur++;
    }
  }
  auto parse_object() -> parse_status { return parse_status::internal_error; }
  auto parse_array() -> parse_status { return parse_status::internal_error; }
  auto parse_string() -> parse_status { return parse_status::internal_error; }
  auto parse_true() -> parse_status { return parse_status::internal_error; }
  auto parse_false() -> parse_status { return parse_status::internal_error; }
  auto parse_value() -> parse_status {
    skip_whitespace();
    if (is_end())
      return parse_status::unexpected_eof;
    auto c = *cur;
    if (c == '{')
      return parse_object();
    else if (c == '[')
      return parse_array();
    else if (c == '"')
      return parse_string();
    else if (c == 't')
      return parse_true();
    else if (c == 'f')
      return parse_false();
    return parse_status::internal_error;
  }
};
} // namespace internal
template <typename P, typename It>
constexpr parse_status parse_json(It begin, It end, P& proxy) {
  auto p = internal::parser{begin, begin, end, proxy};
  return p.parse_value();
}
} // namespace s2::json
