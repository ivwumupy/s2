#pragma once

namespace s2::platform::macos::objc {
namespace internal {
struct send_message_procs {
  static void* send_message;
};
} // namespace internal
struct selector_ref {
  void* inner;
};
struct object_ref {
  void* inner;

  void retain();
  void release();
};
struct class_ref {
  void* inner;
  operator object_ref() { return {inner}; }
};
class_ref get_class(char const* name);
selector_ref register_selector(char const* name);
template <typename R, typename... Args>
R send_message(object_ref obj, selector_ref sel, Args... args) {
  using Proc = R (*)(void*, void const*, Args...);
  return reinterpret_cast<Proc>(internal::send_message_procs::send_message)(
      obj.inner, sel.inner, args...);
}
} // namespace s2::platform::macos::objc
