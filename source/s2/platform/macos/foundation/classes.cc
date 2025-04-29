#include "s2/platform/macos/foundation/classes.h"

//
#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos::foundation {
#define S2_OBJC_CLASS(name)                                                    \
  objc::class_ref classes::name = objc::get_class(#name);
#include "s2/platform/macos/foundation/classes.inc"
#undef S2_OBJC_CLASS
} // namespace s2::platform::macos::foundation
