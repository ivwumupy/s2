#pragma once

#include "s2/ui/render_manager.h"

//
#import <Metal/Metal.h>

namespace s2::ui {
class macos_render_manager final : public render_manager {
public:
  macos_render_manager();
  ~macos_render_manager();

  void setup_window(window* w) override;
  void render_batch(window* w, draw_batch const& b) override;

private:
  void init_shaders();
  void init_pipelines();
  void init_pass_desc();

  id<MTLDevice> device_;
  id<MTLCommandQueue> queue_;
  id<MTLLibrary> shaders_;

  id<MTLRenderPipelineState> triangle_pipeline_;
  id<MTLRenderPipelineState> color_wheel_pipeline_;

  MTLRenderPassDescriptor* pass_desc_;
};
} // namespace s2::ui
