#pragma once

namespace s2::ui {
class draw_batch;
class window;
class render_manager {
public:
  virtual ~render_manager() = default;
  virtual void setup_window(window* w) = 0;
  virtual void render_batch(window* w, draw_batch const& b) = 0;
};
} // namespace s2::ui
