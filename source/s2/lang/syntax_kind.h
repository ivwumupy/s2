#pragma once

namespace s2::lang {
enum class syntax_kind {
#define s2_syntax_leaf(x) x,
#define s2_syntax_node(x) x,
#include "s2/lang/syntax_kind.inc"
};
auto syntax_name(syntax_kind kind) -> char const*;
auto is_leaf_syntax(syntax_kind kind) -> bool;
} // namespace s2::lang
