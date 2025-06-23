#pragma once

#include "s2/base/move.h"

namespace s2 {
template <typename E> class unexpected {
public:
  template <typename F>
  constexpr explicit unexpected(F&& f) : e_{base::forward<F>(f)} {}

  constexpr auto error() & noexcept -> E& { return e_; }
  constexpr auto error() const& noexcept -> E const& { return e_; }
  constexpr auto error() && noexcept -> E&& { return base::move(e_); }

private:
  E e_;
};
} // namespace s2
