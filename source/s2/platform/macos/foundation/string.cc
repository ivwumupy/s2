#include "s2/platform/macos/foundation/string.h"

//
#include "s2/platform/macos/foundation/classes.h"
#include "s2/platform/macos/foundation/selectors.h"
#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos::foundation {
string* string::string_with_utf8_string(const char* cstr) {
  return classes::NSString.as_object().send_message<string*>(
      selectors::stringWithUTF8String_, cstr);
}
uinteger string::length() {
  return as_object().send_message<uinteger>(selectors::length);
}
auto string::utf8_string() -> char const* {
  return as_object().send_message<char const*>(selectors::UTF8String);
}
} // namespace s2::platform::macos::foundation
