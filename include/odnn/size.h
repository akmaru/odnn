#pragma once

#include <cstdint>
#include <numeric>
#include <vector>

#include "array_ref.h"
#include "log.h"

namespace odnn {

class Size {
public:
  using ElemT = std::int64_t;
  using NumT = std::size_t;

  using iterator = ElemT*;
  using const_iterator = const ElemT*;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  Size() : sizes_({}) {}
  explicit Size(ArrayRef<ElemT> arr) : sizes_(arr.to_vector()) {}

  inline ElemT operator[](NumT index) const noexcept { return sizes_[index]; }

  inline ElemT at(NumT index) const {
    CHECK_LT(index, size());
    return this->operator[](index);
  }

  operator ArrayRef<ElemT>() const { return ArrayRef(sizes_); }

  NumT size() const noexcept { return sizes_.size(); }

  NumT num_of_elements() const noexcept {
    if (sizes_.empty()) {
      return 0;
    }

    return std::reduce(sizes_.begin(), sizes_.end(), 1, std::multiplies<>());
  }

  Size strides() const noexcept {
    auto strides = *this;
    std::inclusive_scan(this->crbegin(), this->crend(), strides.rbegin(), std::multiplies<>(), 1);
    return strides;
  }

  iterator begin() noexcept { return sizes_.data(); }
  iterator end() noexcept { return sizes_.data() + size(); }

  const_iterator cbegin() const noexcept { return sizes_.data(); }
  const_iterator cend() const noexcept { return sizes_.data() + size(); }

  reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
  reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

  const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }
  const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

protected:
  std::vector<ElemT> sizes_;
};

}  // namespace odnn
