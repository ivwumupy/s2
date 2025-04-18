#include "ui/ui.h"

struct su_scene {
  sb_allocator_t alloc;
};

su_scene_id su_create_scene(sb_allocator_t alloc) {
  su_scene_id s;
  s = sb_alloc(alloc, sizeof(struct su_scene));
  s->alloc = alloc;
  return s;
}

void su_destroy_scene(su_scene_id s) {
  sb_allocator_t alloc;
  alloc = s->alloc;
  sb_free(alloc, s);
}
