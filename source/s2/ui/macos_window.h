#pragma once

#include "s2/base/basic_types.h"
#include "s2/ui/window.h"

//
#import <AppKit/AppKit.h>

namespace s2::ui::internal {
class ns_window_bridge {
public:
  virtual ~ns_window_bridge() {}
  virtual void ns_windowWillClose(NSNotification* notification) = 0;
  virtual bool ns_windowShouldClose(NSWindow* sender) = 0;
};
} // namespace s2::ui::internal

@interface s2_ns_window_delegate : NSObject <NSWindowDelegate>
- (instancetype)initWithBridge:(s2::ui::internal::ns_window_bridge*)bridge;
@end

namespace s2::ui {
class macos_window final : public window, public internal::ns_window_bridge {
public:
  macos_window(sint width, sint height);
  ~macos_window();

  void set_title() override;

  void ns_windowWillClose(NSNotification* notification) override;
  bool ns_windowShouldClose(NSWindow* sender) override;

private:
  NSWindow* window_;
  s2_ns_window_delegate* ns_delegate_;
};
} // namespace s2::ui
