#pragma once

#include "s2/ui/view.h"

namespace s2::ui::views {
class vstack : public view {};
class quad : public view {
public:
  quad(rect_size size) : size_{size} {}

  rect_size measure(size_proposal proposal) override { return size_; }

  void paint(paint_context& ctx) override { ctx.add_rect(); }

private:
  rect_size size_;
};
class vspace : public view {};
class padding : public view {};
class border : public view {};
} // namespace s2::ui::views
