#include "s2/base/string_view.h"
#include "s2/lang/lexer.h"
#include "s2/test/expects.h"
#include "s2/test/test_case.h"

namespace s2 {
namespace {
using namespace lang;
using test::test_case;
auto check_one(base::string_view source, syntax_kind kind, usize len) {
  lexer l(source.begin(), source.end());
  auto tok = l.lex();
  s2_expect_eq(tok.kind, kind);
  s2_expect_eq(tok.text.length(), len);
}
auto check_list(
  base::string_view source, base::initializer_list<syntax_kind> ks) {
  lexer l(source.begin(), source.end());
  for (auto k : ks) {
    auto tok = l.lex();
    s2_expect_eq(tok.kind, k);
  }
}
test_case end_of_input{[] {
  check_one("", syntax_kind::end_of_input, 0);
  check_list(" ", {
                    syntax_kind::whitespace,
                    syntax_kind::end_of_input,
                    syntax_kind::end_of_input,
                  });
}};
test_case invalid_byte{[] {
  // valid:   11110uvv 10vvwwww 10xxxxyy 10yyzzzz
  // invalid: 11111000 = f8
  check_one("\xf8", syntax_kind::unknown_character, 1);
}};
test_case whitespace{[] {
  check_one(" ", syntax_kind::whitespace, 1);
  check_one("  ", syntax_kind::whitespace, 2);
  check_one("\n x", syntax_kind::whitespace, 2);
}};
test_case line_comment{[] {
  check_one("//hello", syntax_kind::line_comment, 7);
  check_one("//hello\n\n", syntax_kind::line_comment, 7);
  check_list("//hello\n", //
    {
      syntax_kind::line_comment,
      syntax_kind::whitespace,
      syntax_kind::end_of_input,
    });
  check_list(" //hello\n\n//world\n", //
    {
      syntax_kind::whitespace,
      syntax_kind::line_comment,
      syntax_kind::whitespace,
      syntax_kind::line_comment,
      syntax_kind::whitespace,
      syntax_kind::end_of_input,
    });
}};
test_case symbols{[] {
  check_list("(){};=", //
    {
      syntax_kind::l_paren,
      syntax_kind::r_paren,
      syntax_kind::l_brace,
      syntax_kind::r_brace,
      syntax_kind::semicolon,
      syntax_kind::equal,
      syntax_kind::end_of_input,
    });
}};
test_case idents{[] {
  check_one("main ", syntax_kind::ident, 4);
  check_one("main;", syntax_kind::ident, 4);
  check_one("main", syntax_kind::ident, 4);
  check_one("main=", syntax_kind::ident, 4);
  check_one("_Ma1n_", syntax_kind::ident, 6);
  check_list("main(){x=y;}", //
    {
      syntax_kind::ident,
      syntax_kind::l_paren,
      syntax_kind::r_paren,
      syntax_kind::l_brace,
      syntax_kind::ident,
      syntax_kind::equal,
      syntax_kind::ident,
      syntax_kind::semicolon,
      syntax_kind::r_brace,
      syntax_kind::end_of_input,
      syntax_kind::end_of_input,
    });
}};
test_case keywords{[] {
  check_one("def main()", syntax_kind::kw_def, 3);
  check_list("def main()", //
    {
      syntax_kind::kw_def,
      syntax_kind::whitespace,
      syntax_kind::ident,
      syntax_kind::l_paren,
      syntax_kind::r_paren,
      syntax_kind::end_of_input,
    });
}};
} // namespace
} // namespace s2
