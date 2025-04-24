#pragma once

namespace s2::ui {
class window_delegate {
public:
  virtual ~window_delegate() = default;

  virtual void will_close() {}
  virtual bool should_close() { return true; }

  virtual void render() {}
};
} // namespace s2::ui
