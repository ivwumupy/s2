#pragma once

#include "s2/base/basic_types.h"

inline constexpr auto operator new(s2::usize, void* p) noexcept -> void* {
  return p;
}
