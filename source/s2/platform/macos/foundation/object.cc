#include "s2/platform/macos/foundation/object.h"

//
#include "s2/platform/macos/foundation/selectors.h"
#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos::foundation {
auto object::release() -> void {
  as_object().send_message<void>(selectors::release);
}
} // namespace s2::platform::macos::foundation
