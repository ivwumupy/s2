#include "s2/platform/macos/metal/classes.h"

//
#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos::metal {
#define S2_OBJC_CLASS(name)                                                    \
  objc::class_ref classes::name = objc::class_ref::get_class(#name);
#include "s2/platform/macos/metal/classes.inc"
#undef S2_OBJC_CLASS
} // namespace s2::platform::macos::metal
