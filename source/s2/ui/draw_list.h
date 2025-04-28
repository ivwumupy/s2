#pragma once

#include "s2/base/array.h"
#include "s2/ui/draw_items.h"

namespace s2::ui {
class draw_list {
public:
  void add_rect() {}

private:
  base::array<draw_item> items_;
};
} // namespace s2::ui
