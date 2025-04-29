#include "s2/platform/macos/foundation/ns_string.h"

//
#include "s2/platform/macos/foundation/classes.h"
#include "s2/platform/macos/foundation/selectors.h"
#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos::foundation {
ns_string* ns_string::string_with_utf8_string(const char* cstr) {
  return objc::send_message<ns_string*>(classes::NSString,
                                        selectors::stringWithUTF8String_, cstr);
}
ns_uinteger ns_string::length() const {
  return objc::send_message<ns_uinteger>(*this, selectors::length);
}
} // namespace s2::platform::macos::foundation
