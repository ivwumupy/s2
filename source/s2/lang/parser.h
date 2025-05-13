#pragma once

#include "s2/lang/green_builder.h"
#include "s2/lang/green_zone.h"
#include "s2/lang/syntax_kind.h"
#include "s2/lang/token.h"

namespace s2::lang {
// The parser builds a green tree from the tokens.
class parser {
public:
  parser(green_zone* zone, base::slice<token> tokens)
      : builder_{zone}, tokens_{tokens}, cur_{tokens.begin()},
        end_{tokens.end()} {}

  auto is_end() const -> bool { return cur_ >= end_; }
  auto advance() -> void { cur_++; }
  auto peek() -> token& { return *cur_; }

  auto parse_source_file() -> green_node*;
  auto parse_item() -> void;
  auto parse_function_item() -> void;
  auto parse_param_list() -> void;
  // auto parse_group_expr() -> void;

  auto parse_name() -> void;

private:
  auto consume(syntax_kind kind) -> void;
  auto eat_whitespace() -> void;

  green_builder builder_;
  base::slice<token> tokens_;
  token* cur_;
  token* end_;
};
} // namespace s2::lang
