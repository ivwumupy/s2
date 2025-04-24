#include "s2/ui/draw_batch.h"

namespace s2::ui {
void draw_batch::add_vertex(float x, float y, float r, float g, float b) {
  vertices.construct_back(x, y, r, g, b);
}
} // namespace s2::ui
