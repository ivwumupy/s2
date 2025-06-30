#pragma once

#include "s2/ui/views/view.h"

#define s2_view_builder_begin(name)                                            \
  struct name##_builder {                                                      \
    using self_type = name##_builder;                                          \
    name##_builder(name* v) : view_{v} {}                                      \
    name* build() { return view_; }                                            \
    name* view_;
// clang-format off
#define s2_view_builder_end() };
// clang-format on
#define s2_view_builder_field_with_default(type, name, default)                \
  type name##_ = default;                                                      \
  self_type& name(type value) {                                                \
    name##_ = value;                                                           \
    return *this;                                                              \
  }

namespace s2::ui::views {
class vstack : public view {
  s2_view_builder_begin(vstack)
    vstack_builder& child() { return *this; }
    s2_view_builder_field_with_default(float, spacing, 10)
  s2_view_builder_end()

public:
  using builder_type = vstack_builder;

  vstack();
};

class quad : public view {
public:
  quad(rect_size size) : size_{size} {}

  rect_size measure([[maybe_unused]] size_proposal proposal) override {
    return size_;
  }

  void paint(draw_list& list) override { list.add_rect(); }

private:
  rect_size size_;
};
class vspace : public view {};
class padding : public view {};
class border : public view {};
class text_label : public view {};
class text_button : public view {};
} // namespace s2::ui::views
