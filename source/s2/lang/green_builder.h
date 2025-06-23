#pragma once

#include "s2/base/vector.h"
#include "s2/lang/green_zone.h"
#include "s2/lang/token.h"

namespace s2::lang {
class green_builder {
public:
  green_builder(green_zone* zone) : zone_{zone} {}

  auto token(token const& tok) -> void {
    auto p = zone_->make_leaf(tok.kind, tok.text);
    children_.construct_back(p);
  }

  auto begin_node(/*syntax_kind kind*/) -> void {
    auto offset = children_.count();
    // parents_.construct_back(kind, offset);
    parents_.construct_back(syntax_kind::placeholder_, offset);
  }

  auto end_node(syntax_kind kind) -> green_node* {
    auto p = parents_[parents_.count() - 1];
    parents_.pop();
    base::slice<green_node*> c{children_.begin() + p.offset, children_.end()};
    base::string_view t{nullptr, nullptr};
    if (c.count() > 0)
      t = {c[0]->text().begin(), c[c.count() - 1]->text().end()};
    // auto n = zone_->make_node(p.kind, t, c);
    auto n = zone_->make_node(kind, t, c);
    children_.ensure_capacity(p.offset + 1);
    children_.set_count(p.offset + 1);
    children_[p.offset] = n;
    return n;
  }

private:
  struct partial_node {
    syntax_kind kind;
    // offset in `children_`
    usize offset;
  };
  green_zone* zone_;
  base::vector<partial_node> parents_;
  base::vector<green_node*> children_;
};

} // namespace s2::lang
