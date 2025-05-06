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
} // namespace s2::platform::macos::metal
