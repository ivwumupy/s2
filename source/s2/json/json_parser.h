#pragma once

#include "s2/base/string_view.h"

namespace s2::json {
enum class parse_status {
  success,
  internal_error,
};
namespace internal {
template <typename It, typename P> struct parser {
  It begin;
  It cur;
  It end;
  P& proxy;

  bool is_end() const { return cur == end; }
  void parse_whitespce() {}
  parse_status parse_value() { return parse_status::internal_error; }
};
} // namespace internal
template <typename P, typename It>
constexpr parse_status parse_json(It begin, It end, P& proxy) {
  auto p = internal::parser{begin, begin, end, proxy};
  return p.parse_value();
}
} // namespace s2::json
