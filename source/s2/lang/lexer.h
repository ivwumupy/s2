#pragma once

#include "s2/base/array.h"
#include "s2/base/string_view.h"
#include "s2/lang/token.h"

namespace s2::lang {
auto tokenize_source(base::string_view source) -> base::array<token>;
} // namespace s2::lang
