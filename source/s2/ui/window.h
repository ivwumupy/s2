#pragma once

namespace s2::ui {
class window {
public:
  virtual ~window() {}
  virtual void set_title() = 0;
};
} // namespace s2::ui
