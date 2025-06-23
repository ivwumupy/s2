#include "s2/lang/green_zone.h"
#include "s2/lang/lexer.h"
#include "s2/lang/parser.h"
#include "s2/test/test_case.h"

namespace s2 {
namespace {
using namespace lang;
using test::test_case;
auto lex_all(base::string_view source) -> base::vector<token> {
  lexer l{source.begin(), source.end()};
  base::vector<token> result;
  while (true) {
    token tok = l.lex();
    result.construct_back(tok);
    if (tok.kind == syntax_kind::end_of_input)
      break;
  }
  return result;
}
test_case basics{[] {
  green_zone zone;
  auto tokens = lex_all("  def main() {}");
  parser p{&zone, tokens.as_slice()};
  auto s = p.parse_source_file();
  s->dump();
}};
} // namespace
} // namespace s2
