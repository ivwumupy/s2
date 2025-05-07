#include "s2/platform/macos/metal/vertex_descriptor.h"

//
#include "s2/platform/macos/metal/selectors.h"

namespace s2::platform::macos::metal {
auto vertex_descriptor::vertex_attribute_descriptor::format() -> vertex_format {
  return as_object().send_message<vertex_format>(selectors::format);
}
auto vertex_descriptor::vertex_attribute_descriptor::set_format(
    vertex_format format) -> void {
  as_object().send_message<void>(selectors::setFormat_, format);
}
auto vertex_descriptor::vertex_attribute_descriptor::offset()
    -> foundation::uinteger {
  return as_object().send_message<foundation::uinteger>(selectors::offset);
}
auto vertex_descriptor::vertex_attribute_descriptor::set_offset(
    foundation::uinteger offset) -> void {
  as_object().send_message<void>(selectors::setOffset_, offset);
}
auto vertex_descriptor::vertex_attribute_descriptor::buffer_index()
    -> foundation::uinteger {
  return as_object().send_message<foundation::uinteger>(selectors::bufferIndex);
}
auto vertex_descriptor::vertex_attribute_descriptor::set_buffer_index(
    foundation::uinteger index) -> void {
  as_object().send_message<void>(selectors::setBufferIndex_, index);
}
auto vertex_descriptor::vertex_attribute_descriptor_array::object(
    foundation::uinteger index) -> vertex_attribute_descriptor* {
  return as_object().send_message<vertex_attribute_descriptor*>(
      selectors::objectAtIndexedSubscript_, index);
}
auto vertex_descriptor::vertex_attribute_descriptor_array::set_object(
    vertex_attribute_descriptor* descriptor, foundation::uinteger index)
    -> void {
  as_object().send_message<void>(selectors::setObject_atIndexedSubscript_,
                                 descriptor, index);
}

} // namespace s2::platform::macos::metal
