#include "s2/lang/parser.h"

namespace s2::lang {
auto parser::parse_source_file() -> green_node* {
  builder_.begin_node(syntax_kind::source_file);
  if (!is_end()) {
    auto& tok = peek();
    if (tok.kind == syntax_kind::l_paren)
      parse_group_expr();
    else
      s2_panic("todo");
  }
  return builder_.end_node();
}
auto parser::parse_function() -> green_node* { return nullptr; }
auto parser::parse_group_expr() -> green_node* {
  builder_.begin_node(syntax_kind::group_expr);
  consume(syntax_kind::l_paren);
  eat_whitespace();
  while (!is_end()) {
    auto& tok = peek();
    if (tok.kind != syntax_kind::l_paren)
      break;
    parse_group_expr();
    eat_whitespace();
  }
  consume(syntax_kind::r_paren);
  return builder_.end_node();
}
auto parser::consume(syntax_kind kind) -> void {
  s2_check(!is_end());
  s2_check(peek().kind == kind);
  builder_.token(peek());
  advance();
}
auto parser::eat_whitespace() -> void {
  if (is_end())
    return;
  auto& t = peek();
  if (t.kind != syntax_kind::whitespace)
    return;
  builder_.token(t);
  advance();
}
} // namespace s2::lang
