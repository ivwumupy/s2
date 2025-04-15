#include "base/base.h"

//
#include <stdlib.h>

static void *libc_alloc(void *ctx, sint size) { return malloc(size); }

static void libc_free(void *ctx, void *ptr) { free(ptr); }

sb_allocator_t sb_default_allocator = {
    .ctx = 0,
    .alloc = libc_alloc,
    .free = libc_free,
};
