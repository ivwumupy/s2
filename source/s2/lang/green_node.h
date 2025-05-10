#pragma once

#include "s2/base/basic_types.h"
#include "s2/base/slice.h"
#include "s2/base/string_view.h"
#include "s2/lang/syntax_kind.h"

namespace s2::lang {
// Layout:
//   leaf: | kind | text |
//   node: | kind | text | n_children | child[0] | ... | child[n] |
class green_node {
public:
  green_node(syntax_kind k, base::string_view t) : kind_{k}, text_{t} {}
  green_node(
    syntax_kind k, base::string_view t, base::slice<green_node*> children);

  auto text() const -> base::string_view { return text_; }

  auto is_leaf() const -> bool;

  auto children_count() const -> usize;

  auto dump(usize l = 0) const -> void;

private:
  auto init_children(base::slice<green_node*> children) -> void;

  syntax_kind kind_;
  base::string_view text_;
};
} // namespace s2::lang
