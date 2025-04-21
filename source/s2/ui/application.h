#pragma once

#include "s2/base/basic_types.h"
#include "s2/base/unique_ptr.h"

namespace s2::ui {
class window;
class application {
public:
  virtual ~application() {}

  virtual void run() = 0;
  virtual base::unique_ptr<window> make_window(sint width, sint height) = 0;
};
base::unique_ptr<application> make_application();
} // namespace s2::ui
