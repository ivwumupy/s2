#pragma once

#include "s2/base/basic_types.h"

namespace s2::ui {
class font {
public:
  virtual ~font() = default;

  virtual sint glyph_count() const = 0;
};
class text_manager {
public:
  virtual ~text_manager() = default;
  virtual font* default_font() = 0;
};
} // namespace s2::ui
