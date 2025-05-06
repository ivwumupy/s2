#pragma once

#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos::metal {
class function;
class render_pipeline_descriptor {
public:
  static render_pipeline_descriptor* alloc();
  render_pipeline_descriptor* init();

  auto set_vertex_function(function* f) -> void;

  auto as_object() -> objc::object_ref { return {this}; }
};
} // namespace s2::platform::macos::metal
