#pragma once

#include "s2/base/vector.h"
#include "s2/base/string_view.h"
#include "s2/lang/token.h"

namespace s2::lang {
class lexer {
public:
  lexer(char const* beg, char const* end)
      : cur_{beg}, end_{end}, current_start_{beg} {}

  auto advance(usize n = 1) -> void { cur_ += n; }
  auto is_end() -> bool { return cur_ >= end_; }
  auto peek() -> char {
    if (is_end())
      return end_of_input;
    return *cur_;
  }
  auto peek_next() -> char {
    if (cur_ + 1 >= end_)
      return end_of_input;
    return cur_[1];
  }
  auto advance_while(auto&& f) -> void {
    while (!is_end()) {
      auto c = peek();
      if (!f(c))
        break;
      advance();
    }
  }
  auto try_eat(base::string_view s) -> bool;

  auto lex() -> token;
  auto lex_ident_or_kw() -> token;

  // one function for every token kind

  auto lex_whitespace() -> token;
  auto lex_line_comment() -> token;
  auto lex_l_paren() -> token;
  auto lex_r_paren() -> token;
  auto lex_l_brace() -> token;
  auto lex_r_brace() -> token;
  auto lex_semicolon() -> token;
  auto lex_equal() -> token;
  auto lex_ident() -> token;

  auto make_token(syntax_kind kind) -> token {
    char const* start = current_start_;
    char const* end = cur_;
    current_start_ = cur_;
    return {kind, base::string_view{start, end}};
  }

private:
  // Note: -1 cannot appear in valid UTF-8 sequences.
  static constexpr char end_of_input = -1;

  char const* cur_;
  char const* end_;
  // start of the current token
  char const* current_start_;
  base::vector<token> toks_;
};
} // namespace s2::lang
