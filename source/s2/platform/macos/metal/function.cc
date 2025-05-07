#include "s2/platform/macos/metal/function.h"

//
#include "s2/platform/macos/metal/selectors.h"
#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos::metal {
auto function::name() -> foundation::string* {
  return as_object().send_message<foundation::string*>(selectors::name);
}
} // namespace s2::platform::macos::metal
