#include "s2/base/inline_array.h"
#include "s2/ui/application.h"
#include "s2/ui/draw_batch.h"
#include "s2/ui/render_manager.h"
#include "s2/ui/text_manager.h"
#include "s2/ui/view.h"
#include "s2/ui/view_host.h"
#include "s2/ui/views/views.h"
#include "s2/ui/window.h"
#include "s2/ui/window_delegate.h"

//
#include <math.h>
#include <stdio.h>

namespace s2::editor {
namespace {
inline constexpr float pi = 3.1415926535f;
struct color {
  float r;
  float g;
  float b;
  static color from_hue(float h) {
    if (h >= 0 && h <= pi / 3) {
      return {1.0, h * 3 / pi, 0};
    }
    if (h >= pi / 3 && h <= 2 * pi / 3) {
      return {2.0f - h * 3 / pi, 1.0, 0};
    }
    if (h >= 2 * pi / 3 && h <= 3 * pi / 3) {
      return {0, 1.0, h * 3 / pi - 2.0f};
    }
    if (h >= 3 * pi / 3 && h <= 4 * pi / 3) {
      return {0, 4.0f - h * 3 / pi, 1.0};
    }
    if (h >= 4 * pi / 3 && h <= 5 * pi / 3) {
      return {h * 3 / pi - 4.0f, 0.0, 1.0};
    }
    if (h >= 5 * pi / 3 && h <= 6 * pi / 3) {
      return {1.0, 0.0, 6.0f - h * 3 / pi};
    }
    return {1.0, 0.0, 0.0};
  }
};
class editor : public ui::window_delegate {
public:
  editor() {
    app_ = ui::make_application();
    win_ = app_->make_window(500, 500);
    win_->set_title();
    win_->set_delegate(this);
    renderer_ = app_->get_render_manager();
    renderer_->setup_window(win_.get());

    tm_ = app_->get_text_manager();
    font_ = tm_->default_font();

    printf("info: default_font: glphy_count = %ld\n", font_->glyph_count());

    build_batch();
  }

  void render() override {
    renderer_->render_batch(win_.get(), batch_);
    printf("render finish!\n");
    win_->stop_animating();
  }

  void run() {
    win_->start_animating();
    app_->run();
  }

private:
  void build_batch() {
    usize N = 96;
    float r = 350;
    float R = 400;
    float theta = 2 * pi / static_cast<float>(N);
    for (usize i = 0; i < N; i++) {
      float a0 = (static_cast<float>(i) - 0.5f) * theta;
      float a1 = (static_cast<float>(i) + 0.5f) * theta;
      float x0 = r * cosf(a0);
      float y0 = r * sinf(a0);
      float x1 = R * cosf(a0);
      float y1 = R * sinf(a0);
      float x2 = r * cosf(a1);
      float y2 = r * sinf(a1);
      float x3 = R * cosf(a1);
      float y3 = R * sinf(a1);
      auto c = color::from_hue(static_cast<float>(i) * theta);
      batch_.add_triangle(x0, y0, x1, y1, x2, y2, c.r, c.g, c.b);
      batch_.add_triangle(x3, y3, x2, y2, x1, y1, c.r, c.g, c.b);
    }
  }

  base::unique_ptr<ui::application> app_;
  base::unique_ptr<ui::window> win_;
  ui::render_manager* renderer_;
  ui::text_manager* tm_;
  ui::font* font_;
  ui::draw_batch batch_;
  ui::view_host host_;
};
class counter_view : public ui::view {
public:
  counter_view() {
    using namespace ui::views;
    // clang-format off
    root_ =
      make_view<vstack>()
        .child()
        .spacing(5)
        .build();
    // clang-format on
  }

private:
  view* root_;
};
} // namespace
} // namespace s2::editor

void test_comptime() { using namespace s2;
  printf("max = %lu\n", base::numeric_limits<usize>::max);
  printf("min = %lu\n", base::numeric_limits<usize>::min);
}

int main() {
  test_comptime();

  constexpr auto x = s2::base::make_integers<3>();
  for (auto i : x) {
    printf("arr => %lu\n", i);
  }

  s2::editor::editor e;
  e.run();
  return 0;
}
