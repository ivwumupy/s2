#include "ui/ui.h"

//
#include "base/base.h"

//
#import <AppKit/AppKit.h>

// [SECTION] Obj-C Interfaces

@interface s2_ApplicationDelegate : NSObject <NSApplicationDelegate>
@end

// [SECTION]
typedef struct {
  sb_allocator_t alloc;
  NSApplication *app;
  s2_ApplicationDelegate *delegate;
} platform_t;

typedef struct {
  sb_allocator_t alloc;
  NSWindow *window;
} window_t;

static su_window_ops_t window_ops = {};

static su_window_id create_window(void *vself, sint width, sint height) {
  const platform_t *self;
  NSScreen *screen;
  NSWindowStyleMask mask;
  NSRect rect;
  NSWindow *window;
  window_t *obj;

  self = vself;
  screen = [NSScreen mainScreen];
  mask = NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable |
         NSWindowStyleMaskResizable | NSWindowStyleMaskTitled;
  rect = NSMakeRect(0, 0, width, height);
  rect.origin.x = (screen.frame.size.width - width) / 2;
  rect.origin.y = (screen.frame.size.height - height) / 2;
  window = [[NSWindow alloc] initWithContentRect:rect
                                       styleMask:mask
                                         backing:NSBackingStoreBuffered
                                           defer:NO
                                          screen:screen];
  window.minSize = NSMakeSize(200, 200);
  [window makeKeyAndOrderFront:nil];

  obj = sb_alloc(self->alloc, sizeof(window_t));
  obj->alloc = self->alloc;
  obj->window = window;

  return (su_window_id){obj, &window_ops};
}

static void start_event_loop(void *vself) {
  platform_t *self;
  self = vself;
  [self->app run];
}

static su_platform_ops_t platform_ops = {
    .create_window = create_window,
    .start_event_loop = start_event_loop,
};

su_platform_id su_create_appkit_platform(sb_allocator_t alloc) {
  NSApplication *app;
  s2_ApplicationDelegate *delegate;
  platform_t *obj;

  app = [NSApplication sharedApplication];
  [app setActivationPolicy:NSApplicationActivationPolicyRegular];

  delegate = [[s2_ApplicationDelegate alloc] init];
  app.delegate = delegate;

  obj = sb_alloc(alloc, sizeof(platform_t));
  sb_check(obj);
  obj->alloc = alloc;
  obj->app = app;
  obj->delegate = delegate;
  return (su_platform_id){obj, &platform_ops};
}

// [SECTION] Obj-C Implementations

@implementation s2_ApplicationDelegate
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:
    (NSApplication *)sender {
  return YES;
}
@end
