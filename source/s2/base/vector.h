#pragma once

#include "s2/base/integers.h"

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
  constexpr vector() : val_{} {}

  constexpr vector(vector const&);
  constexpr vector& operator=(vector const&);
  constexpr vector(vector&&);
  constexpr vector& operator=(vector&&);

  ~vector();

  constexpr void push(T const&);
  template <typename... Args> constexpr void emplace(Args&&... args);
  constexpr void append(vector const&);

  constexpr void pop();

  constexpr T& operator[](usize i);
  constexpr T const& operator[](usize i) const;

private:
  detail::vector_value<T> val_;
};
} // namespace s2::base
