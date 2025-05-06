#include "s2/platform/macos/objc/runtime.h"

//
#include "s2/base/check.h"

extern "C" {
void* objc_getClass(char const*);
void* sel_registerName(char const*);
void objc_msgSend();
// TODO
void* objc_retain(void*);
void objc_release(void*);
}

namespace s2::platform::macos::objc {
namespace internal {
void* send_message_procs::send_message = reinterpret_cast<void*>(&objc_msgSend);
}
void object_ref::retain() { objc_retain(inner); }
void object_ref::release() { objc_release(inner); }
class_ref class_ref::get_class(char const* name) {
  void* p = objc_getClass(name);
  s2_check(p);
  return {p};
}
selector_ref selector_ref::register_selector(char const* name) {
  void* p = sel_registerName(name);
  s2_check(p);
  return {p};
}
} // namespace s2::platform::macos::objc
