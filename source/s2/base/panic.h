#pragma once

#include "s2/base/source_location.h"
#include "s2/base/string_view.h"

namespace s2::base {
[[noreturn]] void panic(string_view message,
                        source_location loc = source_location::current());
}
