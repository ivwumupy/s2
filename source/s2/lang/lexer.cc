#include "s2/lang/lexer.h"

#include <string.h>

namespace s2::lang {
namespace {
auto is_whitespace(char c) { return c == ' ' || c == '\n'; }
auto is_ident_start(char c) {
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || (c == '_');
}
auto is_ident_body(char c) {
  return ('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || (c == '_') ||
         ('0' <= c && c <= '9');
}
} // namespace

auto lexer::try_eat(base::string_view s) -> bool {
  if (cur_ + s.length() > end_)
    return false;
  if (memcmp(cur_, s.data(), s.length()) != 0)
    return false;
  advance(s.length());
  return true;
}

auto lexer::lex() -> token {
  auto c = peek();
  if (c == end_of_input)
    return make_token(syntax_kind::end_of_input);
  if (is_whitespace(c))
    return lex_whitespace();
  if (c == '(')
    return lex_l_paren();
  if (c == ')')
    return lex_r_paren();
  if (c == '{')
    return lex_l_brace();
  if (c == '}')
    return lex_r_brace();
  if (c == ';')
    return lex_semicolon();
  if (c == '=')
    return lex_equal();
  if (c == '/' && peek_next() == '/')
    return lex_line_comment();
  if (is_ident_start(c))
    return lex_ident_or_kw();
  // unknown
  advance();
  return make_token(syntax_kind::unknown_character);
}

auto lexer::lex_ident_or_kw() -> token {
  auto tok = lex_ident();
  if (tok.text == "def")
    tok.kind = syntax_kind::kw_def;
  return tok;
}

auto lexer::lex_whitespace() -> token {
  advance_while(is_whitespace);
  return make_token(syntax_kind::whitespace);
}

auto lexer::lex_line_comment() -> token {
  advance(2);
  advance_while([](char c) { return c != '\n'; });
  return make_token(syntax_kind::line_comment);
}

auto lexer::lex_l_paren() -> token {
  advance();
  return make_token(syntax_kind::l_paren);
}
auto lexer::lex_r_paren() -> token {
  advance();
  return make_token(syntax_kind::r_paren);
}
auto lexer::lex_l_brace() -> token {
  advance();
  return make_token(syntax_kind::l_brace);
}
auto lexer::lex_r_brace() -> token {
  advance();
  return make_token(syntax_kind::r_brace);
}
auto lexer::lex_semicolon() -> token {
  advance();
  return make_token(syntax_kind::semicolon);
}
auto lexer::lex_equal() -> token {
  advance();
  return make_token(syntax_kind::equal);
}
auto lexer::lex_ident() -> token {
  advance_while(is_ident_body);
  return make_token(syntax_kind::ident);
}

} // namespace s2::lang
