#pragma once

#include "s2/base/unique_ptr.h"
#include "s2/ui/text_manager.h"

//
#include <CoreText/CoreText.h>

namespace s2::ui {
class macos_font final : public font {
public:
  macos_font(CTFontRef f);
  ~macos_font();

  sint glyph_count() const { return glyph_count_; }

private:
  CTFontRef font_;
  sint glyph_count_;
};
class macos_text_manager final : public text_manager {
public:
  macos_text_manager();
  ~macos_text_manager();

  font* default_font() override { return default_font_.get(); }

private:
  void create_default_font();

  base::unique_ptr<macos_font> default_font_;
};
} // namespace s2::ui
