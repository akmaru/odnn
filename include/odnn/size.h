#pragma once

#include <odnn/util.h>

#include <cstdint>
#include <numeric>
#include <ranges>
#include <sstream>
#include <string>
#include <vector>

#include "array_ref.h"
#include "logging.h"

namespace odnn {

class Size {
public:
  using RefT = ArrayRef<SizeT>;

  using iterator = SizeT*;
  using const_iterator = const SizeT*;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  Size() : sizes_({}) {}
  Size(RefT arr) : sizes_(arr.to_vector()) {}

  SizeT& operator[](SizeT index) {
    CHECK_LT(index, ndim());
    return sizes_[index];
  }

  const SizeT& operator[](SizeT index) const {
    CHECK_LT(index, ndim());
    return sizes_[index];
  }

  // NOLINTNEXTLINE(google-explicit-constructor)
  operator RefT() const { return RefT(sizes_); }

  SizeT ndim() const noexcept { return static_cast<SizeT>(sizes_.size()); }

  SizeT num_of_elements() const noexcept {
    if (sizes_.empty()) {
      return 0;
    }

    return std::reduce(sizes_.begin(), sizes_.end(), 1, std::multiplies<>());
  }

  Size strides() const noexcept {
    auto strides = *this;

    if (ndim() > 0) {
      strides[ndim() - 1] = 1;
    }

    if (ndim() > 1) {
      std::inclusive_scan(this->crbegin(), this->crend() - 1, strides.rbegin() + 1, std::multiplies<>(), 1);
    }

    return strides;
  }

  iterator begin() noexcept { return sizes_.data(); }
  iterator end() noexcept { return sizes_.data() + sizes_.size(); }

  const_iterator cbegin() const noexcept { return sizes_.data(); }
  const_iterator cend() const noexcept { return sizes_.data() + sizes_.size(); }

  reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
  reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

  const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }
  const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

  std::string to_string() const {
    std::ostringstream oss;
    oss << "(";
    std::size_t i = 0;

    for (const auto& v : sizes_) {
      if (i++ > 0) {
        oss << ", ";
      }
      oss << v;
    }

    oss << ")";
    return oss.str();
  }

  bool inbound(RefT ref) const noexcept {
    if (static_cast<SizeT>(ref.size()) != ndim()) {
      return false;
    }

    for (auto i : std::ranges::views::iota(0, ndim())) {
      if (ref[i] >= this->operator[](i)) {
        return false;
      }
    }

    return true;
  }

protected:
  std::vector<SizeT> sizes_;
};

using SizeRef = Size::RefT;

}  // namespace odnn
