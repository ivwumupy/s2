#include "s2/lang/green_node.h"

#include <stdio.h>

namespace s2::lang {
namespace {
class green_node_dst : public green_node {
public:
  usize children_count;
  green_node* children[1];
};
} // namespace
green_node::green_node(syntax_kind k, base::strings::string_view t,
  base::slice<green_node*> children)
    : green_node(k, t) {
  init_children(children);
}
auto green_node::init_children(base::slice<green_node*> children) -> void {
  auto self = static_cast<green_node_dst*>(this);
  self->children_count = children.count();
  auto bytes = children.as_bytes();
  __builtin_memcpy(self->children, bytes.begin(), bytes.count());
}
auto green_node::is_leaf() const -> bool { return is_leaf_syntax(kind_); }
auto green_node::dump(usize l) const -> void {
  for (usize i = 0; i < 2 * l; i++)
    putchar(' ');
  printf("%s@%lu\n", syntax_name(kind_), text_.length());
  if (is_leaf())
    return;
  auto self = static_cast<green_node_dst const*>(this);
  // printf("debug: %lu    %p\n", self->children_count, (void*)self);
  for (usize i = 0; i < self->children_count; i++)
    self->children[i]->dump(l + 1);
}
} // namespace s2::lang
