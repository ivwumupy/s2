#pragma once

#define sb_panic_here() ::s2::base::panic(__FILE__, __LINE__)

namespace s2::base {
[[noreturn]]
void panic(char const* file, int line);
}
