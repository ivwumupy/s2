#pragma once

#include "s2/platform/macos/foundation/basic_types.h"
#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos::foundation {
class string {
public:
  static string* string_with_utf8_string(char const* cstr);
  uinteger length();

  auto as_object() -> objc::object_ref { return {this}; }
};
} // namespace s2::platform::macos::foundation
