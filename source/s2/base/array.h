#pragma once

#include "s2/base/allocator.h"
#include "s2/base/basic_types.h"
#include "s2/base/construct.h"
#include "s2/base/initializer_list.h"
#include "s2/base/move.h"
#include "s2/base/panic.h"
#include "s2/base/string_view.h"
#include "s2/base/swap.h"

namespace s2::base {
namespace internal {
// It's not possible to grow an `array_storage`.
template <typename T> class array_storage {
public:
  constexpr array_storage() : begin_{nullptr}, end_{nullptr} {}

  array_storage(sint capacity) {
    void* ptr = default_allocator()->alloc(sizeof(T) * capacity);
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

  sint capacity() const { return end_ - begin_; }

  bool is_empty() const { return begin_ == nullptr; }

  void swap_with(array_storage& other) {
    swap(begin_, other.begin_);
    swap(end_, other.end_);
  }

private:
  void release() { default_allocator()->dealloc(begin_); }

  T* begin_;
  T* end_;
};
} // namespace internal
template <typename T> class array {
  using storage_type = internal::array_storage<T>;

public:
  array() : back_{nullptr} {}
  array(initializer_list<T> l) {
    using namespace literals;
    panic("todo"_sv);
  }

  array(array const&) {}
  array& operator=(array const&) { return *this; }

  array(array&&) {}
  array& operator=(array&& other) {
    array tmp = move(other);
    swap_with(tmp);
    return *this;
  }

  ~array() {}

  template <typename... Args> void construct_back(Args&&... args) {
    if (back_ == storage_.end())
      grow(capacity() + 1);
    construct_at<T>(back_, forward<Args>(args)...);
    back_++;
  }

  sint capacity() const { return storage_.capacity(); }
  sint count() const { return back_ - storage_.begin(); }

  T* begin() { return storage_.begin(); }
  T const* begin() const { return storage_.begin(); }
  T* end() { return back_; }
  T const* end() const { return back_; }

  void swap_with(array& other) { storage_.swap_with(other.storage_); }

private:
  // Grow the array such that capacity > c.
  void grow(sint c) {
    sint nc = 2 * capacity();
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

  storage_type storage_;
  T* back_;
};
} // namespace s2::base
