#include "s2/base/console.h"

//
#include "s2/base/check.h"
#include "s2/base/checked_convert.h"

//
#include <unistd.h>

namespace s2::base {
namespace {
// 4KB
static constexpr usize buffer_size = 4096;
} // namespace
auto console::instance() -> console& {
  static console inst;
  return inst;
}
console::console() {
  begin_ = new char[buffer_size];
  end_ = begin_ + buffer_size;
  cur_ = begin_;
}
console::~console() {
  flush();
  delete[] begin_;
}
auto console::write(char c) -> void {
  if (cur_ >= end_) [[unlikely]] {
    flush();
  }
  *cur_ = c;
  cur_++;
}
auto console::write(char const* s, usize len) -> void {
  if (usize(end_ - cur_) < len) [[unlikely]] {
    // there is not enough space
    if (cur_ == begin_) {
      // the buffer is empty, and we don't need to copy to the internal buffer
      // output a multiple of buffer size
      usize bytes_to_output = len - len % buffer_size;
      output(s, bytes_to_output);
      // the remaining data fits into the buffer
      usize remain = len - bytes_to_output;
      copy_to_buffer(s, remain);
      return;
    }
    usize bytes_to_copy = usize(end_ - cur_);
    copy_to_buffer(s, bytes_to_copy);
    flush();
    write(s + bytes_to_copy, len - bytes_to_copy);
    return;
  }
  copy_to_buffer(s, len);
}
auto console::flush() -> void {
  if (cur_ == begin_)
    return;
  usize len = usize(cur_ - begin_);
  output(begin_, len);
  cur_ = begin_;
}
auto console::copy_to_buffer(char const* p, usize len) -> void {
  s2_check(len <= usize(end_ - cur_));
  __builtin_memcpy(cur_, p, len);
  cur_ += len;
}
auto console::output(char const* p, usize len) -> void {
  // TODO: check EINTR or EAGAIN
  auto ret = ::write(1, p, len);
  s2_check(ret != -1 && checked_convert<usize>(ret) == len);
}
} // namespace s2::base
