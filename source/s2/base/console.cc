#include "s2/base/console.h"

namespace s2::base {
auto console::instance() -> console* {
  static console con;
  return &con;
}
auto console::write_impl(byte const* p, usize n) -> void {}
} // namespace s2::base
