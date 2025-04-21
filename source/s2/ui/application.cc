#include "s2/ui/application.h"

namespace s2::ui {
base::unique_ptr<application> make_macos_application();

base::unique_ptr<application> make_application() {
  return make_macos_application();
}
} // namespace s2::ui
