#pragma once

#include "s2/base/concepts.h"
#include "s2/base/move.h"

namespace s2::base {
template <typename E> class unexpected {
public:
  // TODO: U is not unexpected or in_place, and can construct E
  template <typename U>
  constexpr explicit unexpected(U&& u)
    requires(constructible_from<E, U>)
      : error_{forward<U>(u)} {}

  constexpr auto error() & -> E& { return error_; }
  constexpr auto error() const& -> E const& { return error_; }
  constexpr auto error() && -> E&& { return move(error_); }
  constexpr auto error() const&& -> E const&& { return move(error_); }

private:
  E error_;
};
template <typename E> unexpected(E) -> unexpected<E>;
template <typename T, typename E> class expected {
public:
  // actually this is value-initialization
  constexpr expected()
    requires(default_initializable<T>)
      : value_{}, has_value_{false} {}

  constexpr ~expected() {
    if (has_value_) {
      destruct_value();
    } else {
      destruct_error();
    }
  }

private:
  constexpr auto destruct_value() -> void {
    if constexpr (!trivially_destructible<T>) {
      value_.~T();
    }
  }
  constexpr auto destruct_error() -> void {
    if constexpr (!trivially_destructible<E>) {
      error_.~E();
    }
  }

  T value_;
  E error_;
  bool has_value_;
};
} // namespace s2::base
