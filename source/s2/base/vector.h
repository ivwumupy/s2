#pragma once

#include "s2/base/construct.h"
#include "s2/base/integers.h"
#include "s2/base/move.h"

namespace s2::base {
namespace detail {
template <typename T> class vector_value {
public:
  constexpr vector_value() : first_{}, last_{}, end_{} {}
  constexpr vector_value(T* first, T* last, T* end)
      : first_{first}, last_{last}, end_{end} {}

private:
  T* first_;
  T* last_;
  T* end_;
};
} // namespace detail
template <typename T> class vector {
public:
  constexpr vector() : begin_{}, end_{}, cap_{} {}

  constexpr vector(vector const&);
  constexpr vector& operator=(vector const&);
  constexpr vector(vector&&);
  constexpr vector& operator=(vector&&);

  ~vector();

  constexpr auto push(T const& t) -> void { emplace(t); }
  template <typename... Args> constexpr auto emplace(Args&&... args) -> void {
    if (has_space_at_end()) {
      emplace_no_realloc(forward<Args>(args)...);
      return;
    }
    emplace_by_realloc(forward<Args>(args)...);
  }
  constexpr auto append(vector const&) -> void;

  constexpr auto pop() -> void;

  constexpr auto operator[](usize i) -> T& { return begin_[i]; }
  constexpr auto operator[](usize i) const -> T const& { return begin_[i]; }

  constexpr auto begin() -> T* { return begin_; }
  constexpr auto begin() const -> T const* { return begin_; }
  constexpr auto end() -> T* { return end_; }
  constexpr auto end() const -> T const* { return end_; }

private:
  constexpr auto has_space_at_end() -> bool { return end_ < cap_; }
  // emplace an object at end when there is free space
  template <typename... Args>
  constexpr auto emplace_no_realloc(Args&&... args) -> void {
    construct_at<T>(end_, forward<Args>(args)...);
    end_++;
  }
  // emplace when there is no free space
  template <typename... Args>
  constexpr auto emplace_by_realloc(Args&&... args) -> void {}

  // detail::vector_value<T> val_;
  T* begin_;
  T* end_;
  T* cap_;
};
} // namespace s2::base
