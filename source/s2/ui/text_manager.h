#pragma once

namespace s2::ui {
class font;
class text_manager {
public:
  virtual ~text_manager() = default;
  virtual font* default_font() = 0;
};
} // namespace s2::ui
