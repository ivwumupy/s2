#pragma once

#include "s2/ui/text_manager.h"

//
#include <CoreText/CoreText.h>

namespace s2::ui {
class macos_text_manager final : public text_manager {
public:
  macos_text_manager();
  ~macos_text_manager();

  font* default_font() override;

private:
  void create_default_font();

  CTFontRef default_font_;
};
} // namespace s2::ui
