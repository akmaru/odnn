#pragma once

#include <cstdint>
#include <numeric>
#include <ranges>
#include <vector>

#include "array_ref.h"
#include "logging.h"

namespace odnn {

class Size {
public:
  using ElemT = std::int64_t;
  using IndexT = std::size_t;
  using RefT = ArrayRef<ElemT>;

  using iterator = ElemT*;
  using const_iterator = const ElemT*;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  Size() : sizes_({}) {}
  Size(RefT arr) : sizes_(arr.to_vector()) {}

  inline ElemT operator[](IndexT index) const noexcept { return sizes_[index]; }

  inline ElemT at(IndexT index) const {
    CHECK_LT(index, size());
    return this->operator[](index);
  }

  operator RefT() const { return RefT(sizes_); }

  IndexT size() const noexcept { return sizes_.size(); }

  IndexT num_of_elements() const noexcept {
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

  bool inbound(RefT ref) const noexcept {
    if (ref.size() != size()) {
      return false;
    }

    for (auto i : std::views::iota(IndexT(0), size())) {
      if (ref[i] >= this->operator[](i)) {
        return false;
      }
    }

    return true;
  }

protected:
  std::vector<ElemT> sizes_;
};

using SizeRef = Size::RefT;

}  // namespace odnn
