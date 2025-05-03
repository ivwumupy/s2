// #include "s2/base/inline_array.h"
// #include "s2/ui/application.h"
// #include "s2/ui/draw_batch.h"
// #include "s2/ui/render_manager.h"
// #include "s2/ui/text_manager.h"
// #include "s2/ui/view.h"
// #include "s2/ui/view_host.h"
// #include "s2/ui/views/views.h"
// #include "s2/ui/window.h"
// #include "s2/ui/window_delegate.h"

// //
// // #include "s2/platform/macos/foundation/ns_autorelease_pool.h"
// // #include "s2/platform/macos/foundation/ns_string.h"
// // #include "s2/platform/macos/objc/scoped_autorelease.h"

// //
// #include <math.h>
// #include <stdio.h>

// namespace s2::editor {
// namespace {
// inline constexpr float pi = 3.1415926535f;
// struct color {
//   float r;
//   float g;
//   float b;
//   static color from_hue(float h) {
//     if (h >= 0 && h <= pi / 3) {
//       return {1.0, h * 3 / pi, 0};
//     }
//     if (h >= pi / 3 && h <= 2 * pi / 3) {
//       return {2.0f - h * 3 / pi, 1.0, 0};
//     }
//     if (h >= 2 * pi / 3 && h <= 3 * pi / 3) {
//       return {0, 1.0, h * 3 / pi - 2.0f};
//     }
//     if (h >= 3 * pi / 3 && h <= 4 * pi / 3) {
//       return {0, 4.0f - h * 3 / pi, 1.0};
//     }
//     if (h >= 4 * pi / 3 && h <= 5 * pi / 3) {
//       return {h * 3 / pi - 4.0f, 0.0, 1.0};
//     }
//     if (h >= 5 * pi / 3 && h <= 6 * pi / 3) {
//       return {1.0, 0.0, 6.0f - h * 3 / pi};
//     }
//     return {1.0, 0.0, 0.0};
//   }
// };
// class editor : public ui::window_delegate {
// public:
//   editor() {
//     app_ = ui::make_application();
//     win_ = app_->make_window(500, 500);
//     win_->set_title();
//     win_->set_delegate(this);
//     renderer_ = app_->get_render_manager();
//     renderer_->setup_window(win_.get());

//     tm_ = app_->get_text_manager();
//     font_ = tm_->default_font();

//     printf("info: default_font: glphy_count = %ld\n", font_->glyph_count());

//     build_batch();
//   }

//   void render() override {
//     renderer_->render_batch(win_.get(), batch_);
//     printf("render finish!\n");
//     win_->stop_animating();
//   }

//   void run() {
//     win_->start_animating();
//     app_->run();
//   }

// private:
//   void build_batch() {
//     usize N = 96;
//     float r = 350;
//     float R = 400;
//     float theta = 2 * pi / static_cast<float>(N);
//     for (usize i = 0; i < N; i++) {
//       float a0 = (static_cast<float>(i) - 0.5f) * theta;
//       float a1 = (static_cast<float>(i) + 0.5f) * theta;
//       float x0 = r * cosf(a0);
//       float y0 = r * sinf(a0);
//       float x1 = R * cosf(a0);
//       float y1 = R * sinf(a0);
//       float x2 = r * cosf(a1);
//       float y2 = r * sinf(a1);
//       float x3 = R * cosf(a1);
//       float y3 = R * sinf(a1);
//       auto c = color::from_hue(static_cast<float>(i) * theta);
//       batch_.add_triangle(x0, y0, x1, y1, x2, y2, c.r, c.g, c.b);
//       batch_.add_triangle(x3, y3, x2, y2, x1, y1, c.r, c.g, c.b);
//     }
//   }

//   base::unique_ptr<ui::application> app_;
//   base::unique_ptr<ui::window> win_;
//   ui::render_manager* renderer_;
//   ui::text_manager* tm_;
//   ui::font* font_;
//   ui::draw_batch batch_;
//   ui::view_host host_;
// };
// class counter_view : public ui::view {
// public:
//   counter_view() {
//     using namespace ui::views;
//     // clang-format off
//     root_ =
//       make_view<vstack>()
//         .child()
//         .spacing(5)
//         .build();
//     // clang-format on
//   }

// private:
//   view* root_;
// };
// } // namespace
// } // namespace s2::editor

// void test_comptime() {
//   using namespace s2;
//   printf("max = %lu\n", base::numeric_limits<usize>::max);
//   printf("min = %lu\n", base::numeric_limits<usize>::min);
// }

// // namespace macos = s2::platform::macos;

// int main() {
//   // macos::foundation::ns_autorelease_pool::show_pools();
//   // macos::objc::scoped_autorelease scope;
//   // macos::foundation::ns_autorelease_pool::show_pools();

//   // auto s =
//   //     macos::foundation::ns_string::string_with_utf8_string("hello,
//   world!");
//   // printf("s: %lu\n", s->length());
//   // test_comptime();

//   // constexpr auto x = s2::base::make_integers<3>();
//   // for (auto i : x) {
//   //   printf("arr => %lu\n", i);
//   // }

//   // s2::editor::editor e;
//   // e.run();
//   return 0;
// }

#include "s2/base/coroutine.h"
#include "s2/base/raw_ptr.h"
// #include "s2/platform/macos/dispatch/dispatch.h"
#include "s2/exec/just.h"
#include "s2/exec/start_detached.h"
#include "s2/platform/posix/pthread/thread.h"

//
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

namespace {
// the object returned to the caller when the coroutine is initially suspended
struct return_object {
  struct promise_type {
    return_object get_return_object() {
      putchar('0');
      return {};
    }
    s2::base::suspend_always initial_suspend() {
      putchar('1');
      return {};
    }
    s2::base::suspend_always final_suspend() noexcept { return {}; }
    void return_void() {}
    void unhandled_exception() {}
  };
};
struct awaitable {
  // false => result not ready => the coroutine is suspended
  bool await_ready() { return false; }
  // return void => transfer control to the caller/resumer
  void await_suspend(s2::base::coroutine_handle<>) {
    // schedule the (suspended) coroutine to some executor to execute later
  }
  void await_resume() {}
};
return_object counter() {
  awaitable a;
  putchar('2');
  co_await a;
  putchar('3');
  co_return;
}
[[maybe_unused]] void test_coroutine() {
  counter();
  putchar('x');
}
void* foo(void*) {
  sleep(1);
  printf("foo()\n");
  sleep(1);
  printf("foo() after sleep\n");

  return nullptr;
}
[[maybe_unused]] void test_thread() {
  namespace pthread = s2::platform::posix::pthread;
  pthread::thread t;
  pthread::thread::create(t, &foo, nullptr);
  t.join(nullptr);
}
// void test_dispatch() {
//   static constexpr int x[] = {1, 2, 3};
//   s2::platform::macos::dispatch::create_data(&x, sizeof(x));
// }
void test_exec() {
  namespace exec = s2::exec;
  auto s = exec::just(3);
  exec::start_detached(s2::base::move(s));
}
} // namespace

int main() {
  // test_coroutine();
  // test_thread();
  // test_dispatch();
  test_exec();
  return 0;
}
