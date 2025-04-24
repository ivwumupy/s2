#pragma once

#include "s2/base/allocator.h"
#include "s2/base/construct.h"
#include "s2/base/move.h"
#include "s2/base/type_utils.h"
#include "s2/ui/draw_batch.h"
#include "s2/ui/math.h"

namespace s2::ui {
class paint_context {
public:
  void add_vertex(float x, float y, float r, float g, float b) {
    batch_.add_vertex(x, y, r, g, b);
  }

  void add_rect() {}

private:
  draw_batch batch_;
};
struct size_proposal {};
class view {
public:
  virtual ~view() = default;

  // Compute the size of the view under given proposal.
  virtual rect_size measure(size_proposal size) { return {0, 0}; }
  // Place all the children.
  virtual void layout() {}
  virtual void paint(paint_context& ctx) {}

  rect& bounds() { return bounds_; }

  view* parent() { return parent_; }
  void set_parent(view* p) { parent_ = p; }

  template <typename T, typename... Args>
    requires(base::is_derived_from<T, view>)
  T* make_view(Args&&... args) {
    void* ptr = base::default_allocator()->alloc(sizeof(T));
    T* v = base::construct_at<T>(ptr, base::forward<Args>(args)...);
    return v;
  }

private:
  rect bounds_;
  view* parent_ = nullptr;
};
} // namespace s2::ui
