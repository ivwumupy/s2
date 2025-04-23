#pragma once

#include "s2/base/basic_types.h"
#include "s2/ui/window.h"

//
#import <AppKit/AppKit.h>
#import <QuartzCore/CoreAnimation.h>

namespace s2::ui::internal {
class ns_window_bridge {
public:
  virtual ~ns_window_bridge() = default;
  virtual void ns_windowWillClose(NSNotification* notification) = 0;
  virtual bool ns_windowShouldClose(NSWindow* sender) = 0;
};
class ns_view_bridge {
public:
  virtual ~ns_view_bridge() = default;
  virtual void ns_viewDidChangeBackingProperties() = 0;
  virtual void ns_setFrameSize(NSSize newSize) = 0;
  virtual void ns_setBoundsSize(NSSize newSize) = 0;
};
} // namespace s2::ui::internal

@interface s2_ns_window_delegate : NSObject <NSWindowDelegate>
- (instancetype)initWithBridge:(s2::ui::internal::ns_window_bridge*)bridge;
@end

@interface s2_metal_view : NSView
- (instancetype)initWithBridge:(s2::ui::internal::ns_view_bridge*)bridge;
@end

namespace s2::ui {
class macos_window final : public window,
                           public internal::ns_window_bridge,
                           public internal::ns_view_bridge {
public:
  macos_window(sint width, sint height);
  ~macos_window();

  void set_title() override;

  void ns_windowWillClose(NSNotification* notification) override;
  bool ns_windowShouldClose(NSWindow* sender) override;

  void ns_viewDidChangeBackingProperties() override;
  void ns_setFrameSize(NSSize newSize) override;
  void ns_setBoundsSize(NSSize newSize) override;

  CAMetalLayer* metal_layer() { return metal_layer_; }

private:
  NSWindow* window_;
  s2_ns_window_delegate* ns_delegate_;
  s2_metal_view* ns_view_;
  CAMetalLayer* metal_layer_;
};
} // namespace s2::ui
