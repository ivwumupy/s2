#pragma once

#include "s2/base/allocator.h"
#include "s2/base/basic_types.h"
#include "s2/base/construct.h"
#include "s2/base/panic.h"
#include "s2/base/slice.h"
#include "s2/lang/green_node.h"

namespace s2::lang {
class green_zone {
public:
  green_zone() {
    current_page_ =
      static_cast<base::byte*>(base::default_allocator()->alloc(page_size));
    pos_ = current_page_;
    end_ = current_page_ + page_size;
  }

  ~green_zone() {
    if (current_page_)
      base::default_allocator()->dealloc(current_page_);
  }

  auto make_leaf(syntax_kind kind, base::string_view text) -> green_node* {
    auto p = alloc(sizeof(green_node));
    return base::construct_at<green_node>(p, kind, text);
  }

  auto make_node(syntax_kind kind, base::string_view text,
    base::slice<green_node*> children) -> green_node* {
    auto size = sizeof(green_node) + 8 + 8 * children.count();
    auto p = alloc(size);
    return base::construct_at<green_node>(p, kind, text, children);
  }

private:
  // 4 KB
  static constexpr usize page_size = 4 * 1024;

  auto alloc(usize size) -> void* {
    if (pos_ + size > end_)
      s2_panic("page overflow");
    auto p = pos_;
    pos_ += size;
    return p;
  }

  base::byte* current_page_;
  base::byte* pos_;
  base::byte* end_;
};
} // namespace s2::lang
