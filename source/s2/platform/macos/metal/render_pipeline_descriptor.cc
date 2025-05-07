#include "s2/platform/macos/metal/render_pipeline_descriptor.h"

//
#include "s2/platform/macos/metal/classes.h"
#include "s2/platform/macos/metal/selectors.h"

namespace s2::platform::macos::metal {
auto render_pipeline_descriptor::alloc() -> render_pipeline_descriptor* {
  return classes::MTLRenderPipelineDescriptor.as_object()
      .send_message<render_pipeline_descriptor*>(selectors::alloc);
}
auto render_pipeline_descriptor::init() -> render_pipeline_descriptor* {
  return as_object().send_message<render_pipeline_descriptor*>(selectors::init);
}
auto render_pipeline_descriptor::color_attachment_descriptor::set_pixel_format(
    pixel_format format) -> void {
  as_object().send_message<void>(selectors::setPixelFormat_, format);
}

auto render_pipeline_descriptor::color_attachment_descriptor_array::object(
    foundation::uinteger index) -> color_attachment_descriptor* {
  return as_object().send_message<color_attachment_descriptor*>(
      selectors::objectAtIndexedSubscript_, index);
}
auto render_pipeline_descriptor::color_attachment_descriptor_array::set_object(
    color_attachment_descriptor* attachment, foundation::uinteger index)
    -> void {
  as_object().send_message<void>(selectors::setObject_atIndexedSubscript_,
                                 attachment, index);
}
} // namespace s2::platform::macos::metal
