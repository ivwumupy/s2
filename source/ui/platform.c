#include "ui/ui.h"

//
#include "base/base.h"

su_platform_id su_create_appkit_platform(sb_allocator_t alloc);

su_platform_id su_create_platform(sint kind, sb_allocator_t alloc) {
  switch (kind) {
  case SU_PLATFORM_APPKIT:
    return su_create_appkit_platform(alloc);
  default:
    sb_panic("unimplemented");
  }
}
