#pragma once

#include "s2/base/allocator.h"
#include "s2/base/construct.h"
#include "s2/base/move.h"
#include "s2/base/swap.h"

namespace s2::base {
template <typename T> class unique_ptr {
public:
  constexpr unique_ptr() : ptr_{nullptr} {}

  constexpr unique_ptr(T* ptr) : ptr_{ptr} {}

  template <typename U>
    requires(is_convertible<U*, T*>)
  constexpr unique_ptr(unique_ptr<U>&& other) : ptr_{other.release()} {}

  unique_ptr(unique_ptr const&) = delete;
  unique_ptr& operator=(unique_ptr const&) = delete;

  unique_ptr(unique_ptr&& other) : ptr_{other.release()} {}
  unique_ptr& operator=(unique_ptr&& other) {
    unique_ptr tmp = move(other);
    swap_with(tmp);
    return *this;
  }

  ~unique_ptr() {
    if (ptr_) {
      destruct_at(ptr_);
      default_allocator().dealloc(ptr_);
    }
  }

  T* operator->() { return ptr_; }
  T const* operator->() const { return ptr_; }

  T* release() {
    T* ptr{ptr_};
    ptr_ = nullptr;
    return ptr;
  }

  void swap_with(unique_ptr& other) { swap(ptr_, other.ptr_); }

private:
  T* ptr_;
};
template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&... args) {
  void* ptr = default_allocator().alloc(sizeof(T));
  return unique_ptr<T>{construct_at<T>(ptr, base::forward<Args>(args)...)};
}
} // namespace s2::base
