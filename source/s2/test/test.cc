#include "s2/test/test.h"

//
#include "s2/test/test_manager.h"

namespace s2::test {
test_base::test_base() { test_manager::instance()->register_test(this); }
} // namespace s2::test
