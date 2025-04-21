#pragma once

namespace s2::base {
class view {
public:
  virtual void layout();
  virtual void paint();

protected:
  virtual void request_paint();
};
} // namespace s2::base
