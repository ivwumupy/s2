#pragma once

namespace s2::platform::macos::metal {
class mtl_buffer;
class mtl_command_queue;
class mtl_library;
class mtl_render_pipeline_state;
class mtl_device {
public:
  static mtl_device* create_system_default();
  ~mtl_device();

  mtl_library* make_library();
  mtl_render_pipeline_state* make_render_pipeline_state();
  mtl_command_queue* make_command_queue();
  mtl_buffer* make_buffer();
};
} // namespace s2::platform::macos::metal
