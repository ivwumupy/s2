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

using sint = i64;

namespace internal {
#if defined(S2_PLATFORM_WIN32)
using size_t = unsigned long long;
#else
using size_t = unsigned long;
#endif
} // namespace internal

} // namespace s2::base

namespace s2 {
using base::sint;
}
