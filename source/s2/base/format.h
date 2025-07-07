#pragma once

namespace s2::base {
// specialization:
// template <>
// struct formatter<my_type> {
//
// };
template <typename T> struct formatter;
struct format_context {};
} // namespace s2::base
