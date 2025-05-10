#pragma once

#include "s2/base/array.h"
#include "s2/lang/green_zone.h"
#include "s2/lang/syntax_kind.h"
#include "s2/lang/token.h"

namespace s2::lang {
// The parser builds a green tree from the tokens.
class parser {
public:
  parser(green_zone* zone, base::slice<token> tokens)
      : builder_{zone}, tokens_{tokens}, cur_{tokens.begin()},
        end_{tokens.end()} {}

  auto is_end() const -> bool { return cur_ >= end_; }
  auto advance() -> void { cur_++; }
  auto peek() -> token& { return *cur_; }

  auto parse_source_file() -> green_node*;
  auto parse_function() -> green_node*;
  auto parse_group_expr() -> green_node*;

private:
  class tree_builder {
  public:
    tree_builder(green_zone* zone) : zone_{zone} {}

    auto token(token const& tok) -> void {
      auto p = zone_->make_leaf(tok.kind, tok.text);
      children_.construct_back(p);
    }

    auto begin_node(syntax_kind kind) -> void {
      auto offset = children_.count();
      parents_.construct_back(kind, offset);
    }

    auto end_node() -> green_node* {
      auto p = parents_[parents_.count() - 1];
      parents_.pop();
      base::slice<green_node*> c{children_.begin() + p.offset, children_.end()};
      base::string_view t{nullptr, nullptr};
      if (c.count() > 0)
        t = {c[0]->text().begin(), c[c.count() - 1]->text().end()};
      auto n = zone_->make_node(p.kind, t, c);
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
    base::array<partial_node> parents_;
    base::array<green_node*> children_;
  };

  auto consume(syntax_kind kind) -> void;
  auto eat_whitespace() -> void;

  tree_builder builder_;
  base::slice<token> tokens_;
  token* cur_;
  token* end_;
};
} // namespace s2::lang
