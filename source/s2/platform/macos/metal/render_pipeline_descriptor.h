#pragma once

#include "s2/platform/macos/foundation/basic_types.h"
#include "s2/platform/macos/foundation/object.h"
#include "s2/platform/macos/metal/pixel_format.h"

namespace s2::platform::macos::metal {
class function;
}

namespace s2::platform::macos::metal {
class render_pipeline_descriptor : public foundation::object {
public:
  class color_attachment_descriptor : public foundation::object {
  public:
    auto set_pixel_format(pixel_format format) -> void;
  };
  class color_attachment_descriptor_array : public foundation::object {
  public:
    auto object(foundation::uinteger index) -> color_attachment_descriptor*;
    auto set_object(color_attachment_descriptor* attachment,
                    foundation::uinteger index) -> void;
  };

  static render_pipeline_descriptor* alloc();
  render_pipeline_descriptor* init();

  auto set_vertex_function(function* f) -> void;
};
} // namespace s2::platform::macos::metal
