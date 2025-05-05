#pragma once

#include "s2/base/basic_types.h"
#include "s2/base/string_view.h"
#include "s2/lang/green_kind.h"

namespace s2::lang {
struct green_token {
  green_kind kind;
  base::string_view text;
};
struct green_node {
  green_kind kind;
  usize length;
};
} // namespace s2::lang
