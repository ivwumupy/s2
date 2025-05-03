#pragma once

#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos::metal {
struct selectors {
#define S2_OBJC_SELECTOR(name, str) static objc::selector_ref name;
#include "s2/platform/macos/metal/selectors.inc"
#undef S2_OBJC_SELECTOR
};
} // namespace s2::platform::macos::metal
