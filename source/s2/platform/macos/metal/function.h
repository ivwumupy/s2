#pragma once

#include "s2/platform/macos/foundation/object.h"

namespace s2::platform::macos {
namespace foundation {
class string;
}
} // namespace s2::platform::macos

namespace s2::platform::macos::metal {
class function : public foundation::object {
public:
  auto name() -> foundation::string*;
};
} // namespace s2::platform::macos::metal
