#pragma once

#include "s2/base/strings/string_view.h"
#include "s2/lang/syntax_kind.h"

namespace s2::lang {
struct token {
  syntax_kind kind;
  base::strings::string_view text;
};
} // namespace s2::lang
