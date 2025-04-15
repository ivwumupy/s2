#include "base/base.h"
#include "ui/ui.h"

int main() {
  su_platform_id p =
      su_create_platform(SU_PLATFORM_APPKIT, sb_default_allocator);
  su_window_id w = su_create_window(p, 500, 500);
  su_start_event_loop(p);
  return 0;
}
