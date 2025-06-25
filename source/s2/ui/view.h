#pragma once

#include "s2/base/allocator.h"
#include "s2/base/containers/vector.h"
#include "s2/base/construct.h"
#include "s2/base/move.h"
#include "s2/base/type_utils.h"
#include "s2/ui/draw_list.h"
#include "s2/ui/geometry.h"

namespace s2::ui {
struct size_proposal {};
class view {
public:
  virtual ~view();

  // Compute the size of the view under given proposal.
  virtual rect_size measure([[maybe_unused]] size_proposal size) {
    return {0, 0};
  }
  // Place all the children.
  virtual void layout() {}
  virtual void paint([[maybe_unused]] draw_list& list) {}

  rect& bounds() { return bounds_; }

  view* parent() { return parent_; }
  void set_parent(view* p) { parent_ = p; }

  void add_child(view* child) { children_.construct_back(child); }

  template <typename T, typename... Args>
    requires(base::is_derived_from<T, view>)
  T::builder_type make_view(Args&&... args) {
    T* p = base::v2::default_allocator<T>{}.alloc();
    T* v = base::construct_at<T>(p, base::forward<Args>(args)...);
    return typename T::builder_type{v};
  }

private:
  rect bounds_;
  view* parent_ = nullptr;
  base::containers::vector<view*> children_;
};
} // namespace s2::ui
