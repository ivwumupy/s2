#include "s2/platform/macos/foundation/autorelease_pool.h"

//
#include "s2/platform/macos/foundation/classes.h"
#include "s2/platform/macos/foundation/selectors.h"

namespace s2::platform::macos::foundation {
void autorelease_pool::show_pools() {
  classes::NSAutoreleasePool.as_object().send_message<void>(
      selectors::showPools);
}
} // namespace s2::platform::macos::foundation
