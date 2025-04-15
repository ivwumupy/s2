#pragma once

#include "base/base.h"

typedef struct {
  void *self;
  const struct su_platform_ops_t *ops;
} su_platform_id;

typedef struct {
  void *self;
  const struct su_window_ops_t *ops;
} su_window_id;

typedef struct su_platform_ops_t {
  su_window_id (*create_window)(void *self, sint width, sint height);
  void (*start_event_loop)(void *self);
} su_platform_ops_t;

typedef struct su_window_ops_t {
} su_window_ops_t;

enum su_platform_kind {
  SU_PLATFORM_APPKIT,
};

su_platform_id su_create_platform(sint kind, sb_allocator_t alloc);

static inline su_window_id su_create_window(su_platform_id p, sint width,
                                            sint height) {
  return p.ops->create_window(p.self, width, height);
}
static inline void su_start_event_loop(su_platform_id p) {
  return p.ops->start_event_loop(p.self);
}
