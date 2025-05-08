#pragma once

namespace s2::base {
[[noreturn]] inline void unreachable() { __builtin_unreachable(); }
} // namespace s2::base
