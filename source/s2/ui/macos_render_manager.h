#pragma once

#include "s2/ui/render_manager.h"

//
#import <Metal/Metal.h>

namespace s2::ui {
class macos_render_manager : public render_manager {
public:
  macos_render_manager();
  ~macos_render_manager();

private:
  void init_shaders();
  void init_pipelines();

  id<MTLDevice> device_;
  id<MTLLibrary> shaders_;
};
} // namespace s2::ui
