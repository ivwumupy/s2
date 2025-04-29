#pragma once

#include "s2/platform/macos/foundation/basic_types.h"
#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos::foundation {
class ns_string {
public:
  static ns_string* string_with_utf8_string(char const* cstr);
  ns_uinteger length() const;

  operator objc::object_ref() const { return {this}; }
};
} // namespace s2::platform::macos::foundation
