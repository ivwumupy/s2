#pragma once

inline constexpr auto operator new(
  [[maybe_unused]] __SIZE_TYPE__ size, void* ptr) -> void* {
  return ptr;
}
