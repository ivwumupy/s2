#pragma once

namespace s2::base {
[[noreturn]] inline void unreachable() { __builtin_trap(); }
} // namespace s2::base
