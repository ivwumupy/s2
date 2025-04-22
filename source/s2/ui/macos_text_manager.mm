#include "s2/ui/macos_text_manager.h"

namespace s2::ui {
macos_text_manager::macos_text_manager() { create_default_font(); }
macos_text_manager::~macos_text_manager() { CFRelease(default_font_); }
void macos_text_manager::create_default_font() {
  default_font_ =
      CTFontCreateUIFontForLanguage(kCTFontUIFontSystem, 0.0, nullptr);
}
} // namespace s2::ui
