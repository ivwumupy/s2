#pragma once

#include "s2/platform/macos/dispatch/dispatch.h"
#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos {
namespace foundation {
class error;
}
namespace metal {
class buffer;
class command_queue;
class library;
class render_pipeline_state;
} // namespace metal
} // namespace s2::platform::macos

namespace s2::platform::macos::metal {
class device {
public:
  static device* create_system_default();

  library* new_library(dispatch::data_ref data, foundation::error** error);
  render_pipeline_state* new_render_pipeline_state();
  command_queue* new_command_queue();
  buffer* new_buffer();

  objc::object_ref as_object() { return {this}; }
};
} // namespace s2::platform::macos::metal
