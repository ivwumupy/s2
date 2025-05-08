#include "s2/test/test_manager.h"

int main() {
  s2::test::test_manager::instance()->run_all();
  return 0;
}
