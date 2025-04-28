#pragma once

namespace s2::ui {
struct point {
  float x;
  float y;
};
struct rect_size {
  float width;
  float height;
};
struct rect {
  point origin;
  rect_size size;
};
} // namespace s2::ui
