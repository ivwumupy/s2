#pragma once

namespace s2::ui {
class view;
class window;
class view_host {
public:
  view_host() {}

  view* root_view() { return root_view_; }
  window* host_window() { return host_window_; }

private:
  view* root_view_;
  window* host_window_;
};
} // namespace s2::ui
