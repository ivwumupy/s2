#include "s2/base/panic.h"
#include "s2/base/string_view.h"

int main() {
  using namespace s2::base::literals;
  s2::base::panic("hello editor"_sv);
  return 0;
}
