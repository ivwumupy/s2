#pragma once

#if defined(__clang__)
#define S2_PLATFORM_CLANG 1
#elif defined(__GNUC__)
#define S2_PLATFORM_GCC 1
#elif defined(_MSC_VER)
#define S2_PLATFORM_MSVC 1
#endif

#if defined(_WIN32)
#define S2_PLATFORM_WIN32 1
#elif defined(__APPLE__)
#define S2_PLATFORM_MACOS 1
#endif