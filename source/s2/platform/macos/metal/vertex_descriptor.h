#pragma once

#include "s2/platform/macos/foundation/basic_types.h"
#include "s2/platform/macos/foundation/object.h"

namespace s2::platform::macos::metal {
enum class vertex_format : foundation::uinteger {
  float2 = 29,
  float3 = 30,
};
class vertex_descriptor : public foundation::object {
public:
  class vertex_attribute_descriptor : public foundation::object {
  public:
    auto format() -> vertex_format;
    auto set_format(vertex_format format) -> void;
    auto offset() -> foundation::uinteger;
    auto set_offset(foundation::uinteger offset) -> void;
    auto buffer_index() -> foundation::uinteger;
    auto set_buffer_index(foundation::uinteger index) -> void;
  };
  class vertex_attribute_descriptor_array : public foundation::object {
  public:
    auto object(foundation::uinteger index) -> vertex_attribute_descriptor*;
    auto set_object(vertex_attribute_descriptor* descriptor,
                    foundation::uinteger index) -> void;
  };
  class vertex_buffer_layout_descriptor : public foundation::object {};
  class vertex_buffer_layout_descriptor_array : public foundation::object {
  public:
    auto object(foundation::uinteger index) -> vertex_buffer_layout_descriptor*;
    auto set_object(vertex_buffer_layout_descriptor* descriptor,
                    foundation::uinteger index) -> void;
  };

  static auto make_default() -> vertex_descriptor*;

  auto reset() -> void;
  auto attributes() -> vertex_attribute_descriptor_array*;
  auto layouts() -> vertex_buffer_layout_descriptor_array*;
};
} // namespace s2::platform::macos::metal
