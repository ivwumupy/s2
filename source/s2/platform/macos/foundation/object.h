#pragma once

#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos::foundation {
class object {
public:
  auto release() -> void;
  objc::object_ref as_object() { return {this}; }
};
} // namespace s2::platform::macos::foundation
