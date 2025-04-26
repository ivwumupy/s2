#include "s2/ui/application.h"

//
#include "s2/config.h"

namespace s2::ui {
#ifdef S2_PLATFORM_MACOS
base::unique_ptr<application> make_macos_application();
#endif

#ifdef S2_PLATFORM_WIN32
base::unique_ptr<application> make_win32_application();
#endif

base::unique_ptr<application> make_application() {
#ifdef S2_PLATFORM_MACOS
  return make_macos_application();
#endif
#ifdef S2_PLATFORM_WIN32
  return make_win32_application();
#endif
}
} // namespace s2::ui
