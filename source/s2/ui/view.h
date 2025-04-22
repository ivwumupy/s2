#pragma once

#include "s2/base/basic_types.h"
#include "s2/ui/draw_batch.h"

namespace s2::ui {
class paint_context {
public:
  void add_vertex(float x, float y, base::u32 color) {
    batch_.add_vertex(x, y, color);
  }

private:
  draw_batch batch_;
};
struct rect {
  float x;
  float y;
  float width;
  float height;
};
struct rect_size {
  float width;
  float height;
};
class view {
public:
  virtual ~view() = default;

  // Compute the size of the view.
  virtual rect_size measure() { return {0, 0}; }
  // Place all the children.
  virtual void layout() {}
  virtual void paint(paint_context& ctx) {}

  rect& bounds() { return bounds_; }

private:
  rect bounds_;
};
} // namespace s2::ui
