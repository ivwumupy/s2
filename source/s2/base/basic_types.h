#pragma once

#include "s2/config.h"

namespace s2::base {

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long;

using i8 = signed char;
using i16 = signed short;
using i32 = signed int;
using i64 = signed long;

using f32 = float;
using f64 = double;

using sint [[deprecated]] = i64;

enum class byte : unsigned char {};

using usize = unsigned long;

namespace internal {
#if defined(S2_PLATFORM_WIN32)
using size_t = unsigned long long;
#elif defined(S2_PLATFORM_MACOS)
using size_t = unsigned long;
#endif
} // namespace internal

} // namespace s2::base

namespace s2 {
using base::usize;
}
