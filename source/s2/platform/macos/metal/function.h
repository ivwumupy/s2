#pragma once

#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos {
namespace foundation {
class string;
}
} // namespace s2::platform::macos

namespace s2::platform::macos::metal {
class function {
public:
  auto name() -> foundation::string*;

  objc::object_ref as_object() { return {this}; }
};
} // namespace s2::platform::macos::metal
