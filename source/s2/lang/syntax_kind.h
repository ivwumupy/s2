#pragma once

namespace s2::lang {
enum class syntax_kind {
  whitespace,
  line_comment,

  l_paren,
  r_paren,
  l_brace,
  r_brace,

  semicolon,
  equal,

  ident,

  kw_def,

  unknown_character,
  end_of_input,
};
}
