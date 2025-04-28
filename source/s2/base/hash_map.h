#pragma once

#include "s2/base/array.h"

namespace s2::base {
// TODO
template <typename K, typename T> class hash_map {
public:
  hash_map();
private:
  array<K> keys_;
  array<T> values_;
};
} // namespace s2::base
