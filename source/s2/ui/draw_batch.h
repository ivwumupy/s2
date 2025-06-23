#pragma once

#include "s2/base/vector.h"

namespace s2::ui {
class draw_batch {
public:
  struct vertex {
    float x;
    float y;
    float r;
    float g;
    float b;
  };

  void add_vertex(float x, float y, float r, float g, float b);

  void add_triangle(float x0, float y0, float x1, float y1, float x2, float y2,
                    float r, float g, float b) {
    add_vertex(x0, y0, r, g, b);
    add_vertex(x1, y1, r, g, b);
    add_vertex(x2, y2, r, g, b);
  }

  base::vector<vertex> vertices;
};
} // namespace s2::ui
