#pragma once

#include "s2/base/basic_types.h"
#include "s2/ui/window.h"

//
#import <AppKit/AppKit.h>
#import <QuartzCore/CoreAnimation.h>

namespace s2::ui::internal {
class s2_ns_window_delegate_bridge {
public:
  virtual ~s2_ns_window_delegate_bridge() = default;
  virtual void ns_windowWillClose(NSNotification* notification) = 0;
  virtual bool ns_windowShouldClose(NSWindow* sender) = 0;
  //
  virtual void ns_render(CADisplayLink* sender) = 0;
};
class s2_metal_view_bridge {
public:
  virtual ~s2_metal_view_bridge() = default;
  // The view has been added to a new view hierarchy.
  virtual void ns_viewDidMoveToWindow() = 0;
  virtual void ns_viewDidChangeBackingProperties() = 0;
  virtual void ns_setFrameSize(NSSize newSize) = 0;
  virtual void ns_setBoundsSize(NSSize newSize) = 0;

  // TODO: move CAMetalDisplayLinkDelegate to a separate object
  virtual void
  ca_metalDisplayLink_needsUpdate(CAMetalDisplayLink* link,
                                  CAMetalDisplayLinkUpdate* update) = 0;
};
} // namespace s2::ui::internal

@interface s2_ns_window_delegate : NSObject <NSWindowDelegate>
- (instancetype)initWithBridge:
    (s2::ui::internal::s2_ns_window_delegate_bridge*)bridge;
@end

@interface s2_metal_view : NSView <CAMetalDisplayLinkDelegate>
- (instancetype)initWithBridge:(s2::ui::internal::s2_metal_view_bridge*)bridge;
@end

namespace s2::ui {
class macos_window final : public window,
                           public internal::s2_ns_window_delegate_bridge,
                           public internal::s2_metal_view_bridge {
public:
  macos_window(sint width, sint height);
  ~macos_window();

  void render();

  void set_title() override;
  void request_render() override;
  void start_animating() override;
  void stop_animating() override;

  void ns_windowWillClose(NSNotification* notification) override;
  bool ns_windowShouldClose(NSWindow* sender) override;
  void ns_render(CADisplayLink* sender) override;

  void ns_viewDidMoveToWindow() override;
  void ns_viewDidChangeBackingProperties() override;
  void ns_setFrameSize(NSSize newSize) override;
  void ns_setBoundsSize(NSSize newSize) override;
  void
  ca_metalDisplayLink_needsUpdate(CAMetalDisplayLink* link,
                                  CAMetalDisplayLinkUpdate* update) override;

  CAMetalLayer* metal_layer() { return metal_layer_; }

  id<CAMetalDrawable> drawable() { return drawable_; }

private:
  void init_window();
  void init_layer();
  void init_view();

  void setup_display_link();

  NSWindow* window_ = nullptr;
  s2_ns_window_delegate* ns_delegate_ = nullptr;
  s2_metal_view* ns_view_ = nullptr;
  CAMetalLayer* metal_layer_ = nullptr;
  CAMetalDisplayLink* display_link_ = nullptr;
  // CADisplayLink* display_link_ = nullptr;
  id<CAMetalDrawable> drawable_ = nullptr;

  float width_;
  float height_;
  bool animating_ = false;
};
} // namespace s2::ui
