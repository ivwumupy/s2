#pragma once

#include "s2/base/array.h"
#include "s2/base/basic_types.h"

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

  void add_vertex(float x, float y, base::u32 color);

  base::array<vertex> vertices;
};
} // namespace s2::ui
