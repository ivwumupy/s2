#pragma once

#define sb_panic_here() sb_panic(__FILE__, __LINE__)

void sb_panic(char const* file, int line) __attribute__((noreturn));
