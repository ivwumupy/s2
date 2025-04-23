#include "s2/ui/application.h"
#include "s2/ui/draw_batch.h"
#include "s2/ui/render_manager.h"
#include "s2/ui/window.h"
#include "s2/ui/window_delegate.h"

namespace s2::editor {
namespace {
class editor : public ui::window_delegate {
public:
  editor() {
    app_ = ui::make_application();
    win_ = app_->make_window(500, 500);
    win_->set_title();
    win_->set_delegate(this);
    renderer_ = app_->get_render_manager();
    renderer_->setup_window(win_.get());

    ui::draw_batch b;
    renderer_->render_batch(win_.get(), b);
  }

  void run() { app_->run(); }

  void will_close() override {}
  bool should_close() override { return true; }

private:
  base::unique_ptr<ui::application> app_;
  base::unique_ptr<ui::window> win_;
  ui::render_manager* renderer_;
};
} // namespace
} // namespace s2::editor

int main() {
  s2::editor::editor e;
  e.run();
  return 0;
}
