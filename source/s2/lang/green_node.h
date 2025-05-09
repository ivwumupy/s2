#pragma once

#include "s2/base/array.h"
#include "s2/base/basic_types.h"
#include "s2/base/variant.h"
#include "s2/lang/syntax_kind.h"
#include "s2/lang/token.h"

namespace s2::lang {
struct green_node {
  syntax_kind kind;
  usize length;
  base::array<base::variant<token, green_node>> children;
};
} // namespace s2::lang
