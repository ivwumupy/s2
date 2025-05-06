#pragma once

#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos::metal {
struct classes {
#define S2_OBJC_CLASS(name) static objc::class_ref name;
#include "s2/platform/macos/metal/classes.inc"
#undef S2_OBJC_CLASS
};
} // namespace s2::platform::macos::foundation
