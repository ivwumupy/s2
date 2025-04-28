#pragma once

#include "s2/base/basic_types.h"
#include "s2/base/unique_ptr.h"

namespace s2::ui {
class window;
class render_manager;
class text_manager;
class application {
public:
  virtual ~application() = default;

  virtual void run() = 0;
  virtual base::unique_ptr<window> make_window(usize width, usize height) = 0;

  virtual render_manager* get_render_manager() = 0;
  virtual text_manager* get_text_manager() = 0;
};
base::unique_ptr<application> make_application();
} // namespace s2::ui
