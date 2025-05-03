#pragma once

namespace s2::platform::macos::objc {
class scoped_autorelease {
public:
  scoped_autorelease();
  ~scoped_autorelease();

  scoped_autorelease(scoped_autorelease const&) = delete;
  scoped_autorelease(scoped_autorelease&&) = delete;

private:
  void* const pool_;
};
} // namespace s2::platform::macos::objc
