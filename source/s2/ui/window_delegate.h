#pragma once

namespace s2::ui {
class window_delegate {
public:
  virtual ~window_delegate() {}

  virtual void will_close() {}
  virtual bool should_close() { return true; }
};
} // namespace s2::ui
