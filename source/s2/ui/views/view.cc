#include "s2/ui/views/view.h"

//
#include "s2/base/construct.h"

namespace s2::ui::views {
view::~view() {
  for (auto child : children_) {
    base::destruct_at(child);
  }
}
} // namespace s2::ui::views
