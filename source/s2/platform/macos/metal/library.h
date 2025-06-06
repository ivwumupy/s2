#pragma once

#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos {
namespace foundation {
class string;
}
namespace metal {
class function;
}
} // namespace s2::platform::macos

namespace s2::platform::macos::metal {
class library {
public:
  auto new_function(foundation::string* name) -> function*;

  auto as_object() -> objc::object_ref { return {this}; }
};
} // namespace s2::platform::macos::metal
