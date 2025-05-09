#include "s2/bench/benchmark.h"

using namespace s2::bench;

namespace {
benchmark dummy{[] {
  for (int i = 0; i < 1000; i++)
    ;
}};
} // namespace
