#pragma once

namespace s2::ui {
class window_delegate;
class window {
public:
  window() : delegate_{nullptr} {}

  virtual ~window() = default;

  virtual void set_title() = 0;

  virtual void request_render() = 0;

  virtual void start_animating() = 0;
  virtual void stop_animating() = 0;

  window_delegate* delegate() { return delegate_; }
  void set_delegate(window_delegate* d) { delegate_ = d; }

private:
  window_delegate* delegate_;
};
} // namespace s2::ui
