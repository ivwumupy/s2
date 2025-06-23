#include "s2/ui/macos_text_manager.h"

//
#include "s2/base/checked_convert.h"

namespace s2::ui {
macos_font::macos_font(CTFontRef f) : font_{f} {
  glyph_count_ = base::checked_convert<usize>(CTFontGetGlyphCount(font_));
  auto name = CTFontCopyFullName(font_);
  CFShow(name);
  CFRelease(name);
}
macos_font::~macos_font() { CFRelease(font_); }
macos_text_manager::macos_text_manager() { create_default_font(); }
macos_text_manager::~macos_text_manager() {}
void macos_text_manager::create_default_font() {
  // 0.0 means default size
  auto f = CTFontCreateUIFontForLanguage(kCTFontUIFontSystem, 0.0, nullptr);
  default_font_ = base::make_unique<macos_font>(f);
}
shaped_line
macos_text_manager::shape_line([[maybe_unused]] base::string_view s) {
  return shaped_line{};
}
} // namespace s2::ui
