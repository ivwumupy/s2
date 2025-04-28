#pragma once

#include "s2/base/variant.h"
#include "s2/ui/geometry.h"

namespace s2::ui {
class font;
struct quad_item {
  rect rect;
};
struct linear_gradient_item {};
struct radial_gradient_item {};
struct conic_gradient_item {};
struct text_item {
  font* font;
};
using draw_item =
    base::variant<quad_item, linear_gradient_item, radial_gradient_item,
                  conic_gradient_item, text_item>;
} // namespace s2::ui
