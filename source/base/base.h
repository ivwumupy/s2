#pragma once

#include <stdbool.h>

// [SECTION] Attributes

#define SB_NORETURN __attribute__((noreturn))

// [SECTION] Basic Types

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long i64;

typedef float f32;
typedef double f64;

/* standard int */
typedef i64 sint;

// [SECTION] Panic and Backtrace
SB_NORETURN void sb_panic_with_info(char const *msg, char const *file,
                                    i32 line);

#define sb_panic(msg) sb_panic_with_info(msg, __FILE__, __LINE__)

void sb_print_backtrace();

// [SECTION] Check

#define sb_check(cond)                                                         \
  do {                                                                         \
    if (!(cond)) {                                                             \
      sb_panic("check `" #cond "` fails");                                     \
    }                                                                          \
  } while (0);

// [SECTION] Allocator

typedef struct {
  void *ctx;
  void *(*alloc)(void *ctx, sint size);
  void (*free)(void *ctx, void *ptr);
} sb_allocator_t;

static inline void *sb_alloc(sb_allocator_t a, sint size) {
  return a.alloc(a.ctx, size);
}

static inline void sb_free(sb_allocator_t a, void *ptr) { a.free(a.ctx, ptr); }

extern sb_allocator_t sb_default_allocator;
