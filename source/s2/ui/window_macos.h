#pragma once

#include "s2/base/basic_types.h"
#include "s2/ui/window.h"

//
#import <AppKit/AppKit.h>

namespace s2::ui {
class macos_window : public window {
public:
  macos_window(sint width, sint height);
  ~macos_window();

private:
  NSWindow* window_;
};
} // namespace s2::ui
