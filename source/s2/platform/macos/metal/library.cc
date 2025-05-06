#include "s2/platform/macos/metal/library.h"

//
#include "s2/platform/macos/metal/selectors.h"

namespace s2::platform::macos::metal {
auto library::new_function(foundation::string* name) -> function* {
  return as_object().send_message<function*>(selectors::newFunctionWithName_,
                                             name);
}
} // namespace s2::platform::macos::metal
