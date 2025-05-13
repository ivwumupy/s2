#include "s2/lang/parser.h"

namespace s2::lang {
// Note:
// - When every `parse_xxx` is entered, `is_end()` is guaranteed to be false.
auto parser::parse_source_file() -> green_node* {
  builder_.begin_node();
  while (true) {
    eat_whitespace();
    if (is_end() || peek().kind == syntax_kind::end_of_input)
      break;
    parse_item();
  }
  return builder_.end_node(syntax_kind::source_file);
}
auto parser::parse_item() -> void {
  auto& tok = peek();
  if (tok.kind == syntax_kind::kw_def)
    parse_function_item();
  // else if (tok.kind == syntax_kind::l_paren)
  //   parse_group_expr();
  else
    s2_panic("todo");
}
auto parser::parse_function_item() -> void {
  builder_.begin_node();
  consume(syntax_kind::kw_def);
  eat_whitespace();
  parse_name();
  eat_whitespace();
  parse_param_list();
  eat_whitespace();
  consume(syntax_kind::l_brace);
  eat_whitespace();
  consume(syntax_kind::r_brace);
  builder_.end_node(syntax_kind::function_item);
}
auto parser::parse_param_list() -> void {
  builder_.begin_node();
  consume(syntax_kind::l_paren);
  eat_whitespace();
  consume(syntax_kind::r_paren);
  builder_.end_node(syntax_kind::param_list);
}
// auto parser::parse_group_expr() -> void {}

auto parser::parse_name() -> void {
  builder_.begin_node();
  consume(syntax_kind::ident);
  builder_.end_node(syntax_kind::name);
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
