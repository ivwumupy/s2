#pragma once

#include "s2/base/allocator.h"
#include "s2/base/basic_types.h"
#include "s2/base/checked_convert.h"
#include "s2/base/construct.h"
#include "s2/base/initializer_list.h"
#include "s2/base/move.h"
#include "s2/base/panic.h"
#include "s2/base/slice.h"
#include "s2/base/swap.h"
#include "s2/base/tag_invoke.h"

namespace s2::base {
namespace internal {
// It's not possible to grow an `array_storage`.
template <typename T> class array_storage {
public:
  constexpr array_storage() : begin_{nullptr}, end_{nullptr} {}

  array_storage(usize capacity) {
    void* ptr = default_allocator<T>{}.alloc_n(capacity);
    begin_ = reinterpret_cast<T*>(ptr);
    end_ = begin_ + capacity;
  }

  array_storage(array_storage&& other)
      : begin_{other.begin_}, end_{other.end_} {
    other.begin_ = nullptr;
    other.end_ = nullptr;
  }
  array_storage& operator=(array_storage&& other) {
    array_storage tmp = move(other);
    swap_with(tmp);
    return *this;
  }

  ~array_storage() {
    if (!is_empty())
      release();
  }

  T* begin() { return begin_; }
  T const* begin() const { return begin_; }
  T* end() { return end_; }
  T const* end() const { return end_; }

  usize capacity() const { return checked_convert<usize>(end_ - begin_); }

  bool is_empty() const { return begin_ == nullptr; }

  void swap_with(array_storage& other) {
    swap(begin_, other.begin_);
    swap(end_, other.end_);
  }

private:
  void release() { default_allocator<T>{}.free_n(begin_, capacity()); }

  T* begin_;
  T* end_;
};
} // namespace internal
namespace array_ {
template <typename T> class vector {
  using storage_type = internal::array_storage<T>;

public:
  vector() : back_{nullptr} {}
  vector([[maybe_unused]] initializer_list<T> l) { s2_panic("todo"); }

  vector(vector const& other) { init_by_copy(other.begin(), other.end()); }
  vector& operator=(vector const& other) {
    vector tmp(other);
    swap_with(tmp);
    return *this;
  }

  vector(vector&& other) : storage_{move(other.storage_)}, back_{other.back_} {
    other.back_ = nullptr;
  }
  vector& operator=(vector&& other) {
    vector tmp = move(other);
    swap_with(tmp);
    return *this;
  }

  ~vector() {}

  template <typename... Args> void construct_back(Args&&... args) {
    if (back_ == storage_.end())
      grow(capacity() + 1);
    construct_at<T>(back_, forward<Args>(args)...);
    back_++;
  }

  auto pop() -> void {
    s2_check(count() > 0);
    auto p = back_ - 1;
    destruct_at(p);
    back_--;
  }

  usize capacity() const { return storage_.capacity(); }
  usize count() const {
    return checked_convert<usize>(back_ - storage_.begin());
  }

  bool is_empty() const { return back_ == storage_.begin(); }

  T* begin() { return storage_.begin(); }
  T const* begin() const { return storage_.begin(); }
  T* end() { return back_; }
  T const* end() const { return back_; }

  auto operator[](usize i) -> T& { return begin()[i]; }
  auto operator[](usize i) const -> T const& { return begin()[i]; }

  auto ensure_capacity(usize c) -> void {
    if (capacity() >= c)
      return;
    grow(c);
  }

  // unsafe
  auto set_count(usize c) -> void { back_ = begin() + c; }

  // unsafe
  auto resize_uninitialized(usize n) -> void {
    ensure_capacity(n);
    set_count(n);
  }

  usize size_in_bytes() const { return count() * sizeof(T); }

  slice<T> as_slice() { return slice<T>{begin(), end()}; }

  void swap_with(vector& other) { storage_.swap_with(other.storage_); }

private:
  void init_by_copy(T const* begin, T const* end) {
    storage_ = storage_type(end - begin);
    for (T *b = begin, *it = storage_.begin(); b < end; b++, it++) {
      construct_at<T>(it, *b);
    }
    back_ = storage_.end();
  }

  // Grow the array such that capacity > c.
  void grow(usize c) {
    usize nc = 2 * capacity();
    if (nc < c)
      nc = c;
    storage_type ns{nc};
    T* nb = ns.begin();
    if (!storage_.is_empty()) {
      for (T* it = storage_.begin(); it < storage_.end(); it++, nb++) {
        construct_at<T>(nb, move(*it));
      }
      for (T* it = storage_.begin(); it < storage_.end(); it++) {
        destruct_at(it);
      }
    }
    storage_.swap_with(ns);
    swap(back_, nb);
  }

  friend void tag_invoke(tag<swap>, vector& lhs, vector& rhs) {
    swap(lhs.storage_, rhs.storage_);
    swap(lhs.back_, rhs.back_);
  }

  storage_type storage_;
  T* back_;
};
} // namespace array_
using array_::vector;
template <typename T, typename... Ts> auto make_array(Ts&&... ts) -> vector<T> {
  constexpr usize n = sizeof...(Ts);
  vector<T> x;
  x.resize_uninitialized(n);
  usize i = 0;
  (construct_at<T>(x.begin() + (i++), forward<Ts>(ts)), ...);
  return x;
}
} // namespace s2::base
