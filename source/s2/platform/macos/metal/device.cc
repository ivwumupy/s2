#include "s2/platform/macos/metal/device.h"

//
#include "s2/platform/macos/metal/selectors.h"

extern "C" {
void* MTLCreateSystemDefaultDevice();
}

namespace s2::platform::macos::metal {
device* device::create_system_default() {
  return reinterpret_cast<device*>(MTLCreateSystemDefaultDevice());
}
command_queue* device::new_command_queue() {
  return as_object().send_message<command_queue*>(selectors::newCommandQueue);
}
auto device::new_library(dispatch::data_ref data, foundation::error** error)
    -> library* {
  return as_object().send_message<library*>(
      selectors::newLibraryWithData_error_, data, error);
}
} // namespace s2::platform::macos::metal
