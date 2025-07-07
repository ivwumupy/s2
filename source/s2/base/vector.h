#pragma once

#include "s2/base/integers.h"

namespace s2::base {
template <typename T> class vector {
public:
  vector();

  vector(vector const&);
  vector& operator=(vector const&);
  vector(vector&&);
  vector& operator=(vector&&);

  ~vector();

  void push(T const&);
  template <typename... Args> void emplace(Args&&... args);
  void append(vector const&);

  void pop();

  T& operator[](usize i);
  T const& operator[](usize i) const;

private:
};
} // namespace s2::base
