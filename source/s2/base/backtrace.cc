#include "s2/base/backtrace.h"

//
#include "s2/base/basic_types.h"
#include "s2/config.h"

//
#include <stdio.h>
#include <string.h>

//
#if defined(S2_PLATFORM_MACOS)
#include <dlfcn.h>
#include <execinfo.h>
#elif defined(S2_PLATFORM_WIN32)
#include <Windows.h>
#include <dbghelp.h>
#endif

namespace s2::base {
namespace {
// [NOTE]
// [Itanium C++ ABI]
// <mangled-name> = "_Z" <encoding> ("." <vendor-specific>)?
// <encoding>
//   = <name[function]> <bare-function-type>
//   | <name[data]>
//   | <special-name>
#if defined(S2_PLATFORM_MACOS)
bool symbolize(void const* pc, char* buf, sint size) {
  Dl_info info;
  if (dladdr(pc, &info)) {
    if (strlen(info.dli_sname) < size) {
      strcpy(buf, info.dli_sname);
      return true;
    }
  }
  return false;
}
#elif defined(S2_PLATFORM_WIN32)
#endif
} // namespace

// [NOTE]
// There is a potential bug: consider the following code
//   [[noreturn]] void panic() { print_backtrace(); __builtin_trap(); }
//   void foo() { panic(); }
// Both GCC and Clang do not generate a `ret` instruction for `foo()`.
// So the address returned by `backtrace()` might point to the next symbol
// following `foo()`.
// One solution is to subtract 1 from the address.
#if defined(S2_PLATFORM_MACOS)
void print_backtrace() {
  void* entries[128];
  char symbol_buffer[256];
  sint count = backtrace(entries, 128);
  char const* name;
  for (sint i = 0; i < count; i++) {
    // See the note above.
    void const* addr = static_cast<char const*>(entries[i]) - 1;
    if (symbolize(addr, symbol_buffer, 256)) {
      name = symbol_buffer;
    } else {
      name = "<unknown>";
    }
    printf("  # %p %s\n", entries[i], name);
  }
}
#elif defined(S2_PLATFORM_WIN32)
void print_backtrace() {
  void* entries[128];
  sint count = CaptureStackBackTrace(0, 128, entries, nullptr);
  for (sint i = 0; i < count; i++) {
    printf("  # %p <unknown>\n", entries[i]);
  }
}
#endif
} // namespace s2::base
