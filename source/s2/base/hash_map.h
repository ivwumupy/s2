#pragma once

#include "s2/base/vector.h"

namespace s2::base {
// TODO
template <typename K, typename T> class hash_map {
public:
  hash_map() {}

private:
  vector<K> keys_;
  vector<T> values_;
};
} // namespace s2::base
