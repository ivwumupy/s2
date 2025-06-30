#pragma once

#include "s2/base/basic_types.h"

namespace s2::platform::macos::objc {
namespace internal {
struct send_message_procs {
  static void* send_message;
};
} // namespace internal
struct selector_ref {
  void* inner;

  static selector_ref register_selector(char const* name);
};
struct object_ref {
  void* inner;

  template <typename R, typename... Args>
  R send_message(selector_ref sel, Args... args) {
    using Proc = R (*)(void*, void const*, Args...);
    return reinterpret_cast<Proc>(internal::send_message_procs::send_message)(
      inner, sel.inner, args...);
  }

  //
  void retain();
  void release();
};
struct class_ref {
  void* inner;

  static class_ref get_class(char const* name);

  static auto allocate_class_pair(
    class_ref super_class, char const* name, usize extra_bytes) -> class_ref;

  auto as_object() -> object_ref { return {inner}; }
};
// class_ref get_class(char const* name);
// selector_ref register_selector(char const* name);
} // namespace s2::platform::macos::objc
