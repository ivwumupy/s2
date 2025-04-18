#include "base/backtrace.h"

//
#include "base/basic_types.h"

//
#include <stdio.h>
#include <string.h>

//
#include <dlfcn.h>
#include <execinfo.h>

namespace s2::base {
namespace {
// [NOTE]
// [Itanium C++ ABI]
// <mangled-name> = "_Z" <encoding> ("." <vendor-specific>)?
// <encoding>
//   = <name[function]> <bare-function-type>
//   | <name[data]>
//   | <special-name>
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
} // namespace

// [NOTE]
// There is a potential bug: consider the following code
//   [[noreturn]] void panic() { print_backtrace(); __builtin_trap(); }
//   void foo() { panic(); }
// Both GCC and Clang do not generate a `ret` instruction for `foo()`.
// So the address returned by `backtrace()` might point to the next symbol
// following `foo()`.
// One solution is to subtract 1 from the address.
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
} // namespace s2::base
