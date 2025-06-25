#pragma once

#include "s2/base/containers/vector.h"

namespace s2::base::containers {
// TODO
template <typename K, typename T> class hash_map {
public:
  hash_map() {}

private:
  vector<K> keys_;
  vector<T> values_;
};
} // namespace s2::base::containers
