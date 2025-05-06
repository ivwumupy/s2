#include "s2/platform/macos/foundation/selectors.h"

//
#include "s2/platform/macos/objc/runtime.h"

namespace s2::platform::macos::foundation {
#define S2_OBJC_SELECTOR(name, str)                                            \
  objc::selector_ref selectors::name =                                         \
      objc::selector_ref::register_selector(str);
#include "s2/platform/macos/foundation/selectors.inc"
#undef S2_OBJC_SELECTOR
} // namespace s2::platform::macos::foundation
