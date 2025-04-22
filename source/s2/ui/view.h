#pragma once

namespace s2::ui {
class view {
public:
  virtual void measure();
  virtual void layout();
  virtual void paint();
};
} // namespace s2::ui
