#pragma once

#define s2_panic(msg) ::s2::base::internal::panic(msg, __FILE__, __LINE__)

namespace s2::base::internal {
[[noreturn]] void panic(char const* msg, char const* file, unsigned int line);
}
