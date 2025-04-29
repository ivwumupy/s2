#include "s2/platform/macos/objc/runtime.h"

//
#include "s2/base/check.h"

extern "C" {
void* objc_getClass(char const*);
void* sel_registerName(char const*);
void objc_msgSend();
}

namespace s2::platform::macos::objc {
namespace internal {
void* send_message_procs::send_message = reinterpret_cast<void*>(&objc_msgSend);
}
class_ref get_class(char const* name) {
  void* p = objc_getClass(name);
  s2_check(p);
  return {p};
}
selector_ref register_selector(char const* name) {
  void* p = sel_registerName(name);
  s2_check(p);
  return {p};
}
} // namespace s2::platform::macos::objc
