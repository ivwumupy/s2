#include "s2/base/console.h"
#include "s2/base/panic.h"

int main(void) {
  s2::base::console::instance().write_line("hello, console");
  s2::base::console::instance().flush();
  s2_panic_here();
  return 0;
}
