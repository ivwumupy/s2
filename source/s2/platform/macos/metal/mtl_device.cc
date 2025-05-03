#include "s2/platform/macos/metal/mtl_device.h"

//
// #include "s2/platform/macos/objc/runtime.h"

extern "C" {
void* MTLCreateSystemDefaultDevice();
}

namespace s2::platform::macos::metal {
mtl_device::~mtl_device() {}
mtl_device* mtl_device::create_system_default() {
  return reinterpret_cast<mtl_device*>(MTLCreateSystemDefaultDevice());
}
} // namespace s2::platform::macos::metal
