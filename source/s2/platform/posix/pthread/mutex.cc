#include "s2/platform/posix/pthread/mutex.h"

extern "C" {
int pthread_mutex_init(void* mutex, void const* attr);
int pthread_mutex_lock(void* mutex);
int pthread_mutex_unlock(void* mutex);
}

namespace s2::platform::posix::pthread {
int mutex::init(mutex& m) { return pthread_mutex_init(&m, nullptr); }
int mutex::lock() { return pthread_mutex_lock(this); }
int mutex::unlock() { return pthread_mutex_unlock(this); }
} // namespace s2::platform::posix::pthread
