#include "s2/platform/posix/pthread/cond.h"

extern "C" {
int pthread_cond_init(void* cond, void const* attr);
int pthread_cond_signal(void* cond);
int pthread_cond_wait(void* cond, void* mutex);
}

namespace s2::platform::posix::pthread {
int cond::init(cond& c) { return pthread_cond_init(&c, nullptr); }
int cond::signal() { return pthread_cond_signal(this); }
int cond::wait(mutex& m) { return pthread_cond_wait(this, &m); }
} // namespace s2::platform::posix::pthread
