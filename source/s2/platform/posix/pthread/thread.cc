#include "s2/platform/posix/pthread/thread.h"

extern "C" {
int pthread_create(void** thread, void const* attr,
                   void* (*start_routine)(void*), void* arg);
int pthread_join(void* thread, void** value);
void* pthread_self();
}

namespace s2::platform::posix::pthread {
int thread::create(thread& t, routine_type start, base::raw_ptr<void> arg) {
  return pthread_create(&t.inner, nullptr, start, arg.as_raw());
}
int thread::join(base::raw_ptr<void*> value) {
  return pthread_join(inner, value.as_raw());
}
} // namespace s2::platform::posix::pthread
