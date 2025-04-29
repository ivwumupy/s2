#pragma once

#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos::foundation {
struct selectors {
#define S2_OBJC_SELECTOR(name, str) static objc::selector_ref name;
#include "s2/platform/macos/foundation/selectors.inc"
#undef S2_OBJC_SELECTOR
};
} // namespace s2::platform::macos::foundation
