#include "s2/platform/macos/foundation/ns_autorelease_pool.h"

//
#include "s2/platform/macos/foundation/classes.h"
#include "s2/platform/macos/foundation/selectors.h"

namespace s2::platform::macos::foundation {
void ns_autorelease_pool::show_pools() {
  objc::send_message<void>(classes::NSAutoreleasePool, selectors::showPools);
}
} // namespace s2::platform::macos::foundation
