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

typedef struct {
  void *self;
  const struct su_renderer_ops *ops;
} su_renderer_id;

typedef struct su_platform_ops_t {
  su_window_id (*create_window)(void *self, sint width, sint height);
  su_renderer_id (*create_renderer)(void *self);
  void (*start_event_loop)(void *self);
} su_platform_ops_t;

typedef struct su_window_ops_t {
} su_window_ops_t;

typedef struct su_renderer_ops_t {

} su_renderer_ops_t;

enum su_platform_kind {
  SU_PLATFORM_APPKIT,
};

su_platform_id su_create_platform(sint kind, sb_allocator_t alloc);

static inline su_window_id su_create_window(su_platform_id p, sint width,
                                            sint height) {
  return p.ops->create_window(p.self, width, height);
}
static inline su_renderer_id su_create_renderer(su_platform_id p) {
  return p.ops->create_renderer(p.self);
}
static inline void su_start_event_loop(su_platform_id p) {
  return p.ops->start_event_loop(p.self);
}

// [SECTION] Fonts

typedef struct {
  void *self;
} su_font_id;

su_font_id su_create_default_font();

// [SECTION] Render
//
// Primitives:
// - rect
// - path?
// - text
//
// Primitives are submitted to GPU in batches.
//
// Approach 1: batch the primitives wh

typedef struct su_scene *su_scene_id;

su_scene_id su_create_scene(sb_allocator_t alloc);
void su_destroy_scene(su_scene_id s);

void su_destroy_renderer(su_renderer_id r);
