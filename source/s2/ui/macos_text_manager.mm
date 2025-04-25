#include "s2/ui/macos_text_manager.h"

namespace s2::ui {
macos_font::macos_font(CTFontRef f) : font_{f} {
  glyph_count_ = CTFontGetGlyphCount(font_);
}
macos_font::~macos_font() { CFRelease(font_); }
macos_text_manager::macos_text_manager() { create_default_font(); }
macos_text_manager::~macos_text_manager() {}
void macos_text_manager::create_default_font() {
  auto f = CTFontCreateUIFontForLanguage(kCTFontUIFontSystem, 0.0, nullptr);
  default_font_ = base::make_unique<macos_font>(f);
}
} // namespace s2::ui
