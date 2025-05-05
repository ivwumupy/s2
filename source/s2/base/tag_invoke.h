#pragma once

#include "s2/base/move.h"
#include "s2/base/type_utils.h"

namespace s2::base {
namespace tag_invoke_ {
void tag_invoke();
struct tag_invoke_tag {
  template <typename Tag, typename... Args>
  constexpr auto operator()(Tag tag, Args&&... args) const noexcept
      -> decltype(auto) {
    return tag_invoke(tag, ::s2::base::forward<Args>(args)...);
  }
};
} // namespace tag_invoke_
inline constexpr tag_invoke_::tag_invoke_tag tag_invoke{};
template <auto t> using tag = decay<decltype(t)>;
} // namespace s2::base
