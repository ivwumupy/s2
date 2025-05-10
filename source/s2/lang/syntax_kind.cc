#include "s2/lang/syntax_kind.h"

namespace s2::lang {
auto syntax_name(syntax_kind k) -> char const* {
  switch (k) {
#define case_(x)                                                               \
  case syntax_kind::x:                                                         \
    return #x;
#define s2_syntax_leaf(x) case_(x)
#define s2_syntax_node(x) case_(x)
#include "s2/lang/syntax_kind.inc"
#undef case_
  }
}
auto is_leaf_syntax(syntax_kind k) -> bool {
  switch (k) {
#define case_(x, v)                                                            \
  case syntax_kind::x:                                                         \
    return v;
#define s2_syntax_leaf(x) case_(x, true)
#define s2_syntax_node(x) case_(x, false)
#include "s2/lang/syntax_kind.inc"
#undef case_
  }
}
} // namespace s2::lang
