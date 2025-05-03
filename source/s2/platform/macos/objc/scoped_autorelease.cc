#include "s2/platform/macos/objc/scoped_autorelease.h"

extern "C" {
void* objc_autoreleasePoolPush();
void objc_autoreleasePoolPop(void*);
}

namespace s2::platform::macos::objc {
scoped_autorelease::scoped_autorelease() : pool_{objc_autoreleasePoolPush()} {}
scoped_autorelease::~scoped_autorelease() { objc_autoreleasePoolPop(pool_); }
} // namespace s2::platform::macos::objc
