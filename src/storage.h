#pragma once

#include <odnn/util.h>

#include <algorithm>
#include <cstdint>
#include <memory>
#include <ranges>

#include "logging.h"

namespace odnn {

template <typename DType>
class Storage {
public:
  using DataT = std::unique_ptr<DType[]>;

  using iterator = DType*;
  using const_iterator = const DType*;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  Storage() : data_(nullptr), size_(0) {}

  explicit Storage(SizeT size) { calloc(size); }

  DType* data() noexcept { return data_.get(); }

  const DType* data() const noexcept { return data_.get(); }

  auto size() const noexcept { return size_; }

  auto bytes() const noexcept { return size() * sizeof(DType); }

  DType& operator[](SizeT index) {
    CHECK_LE(index, size());
    return data()[index];
  }

  const DType& operator[](SizeT index) const {
    CHECK_LE(index, size());
    return data()[index];
  }

  iterator begin() noexcept { return data(); }
  iterator end() noexcept { return data() + size(); }

  const_iterator cbegin() const noexcept { return data(); }
  const_iterator cend() const noexcept { return data() + size(); }

  reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
  reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

  const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }
  const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

  void realloc(SizeT size) {
    data_ = alloc(size);
    size_ = size;
  }

  void fill(DType value) { std::fill(begin(), end(), static_cast<DType>(value)); }

  void fill_zero() { fill(static_cast<DType>(0)); }

  void fill_sequence() {
    const auto index_range = std::ranges::iota_view(0, size());
    std::ranges::for_each(index_range, [&](auto i) mutable {
      this->operator[](i) = static_cast<DType>(i);
    });
  }

  void calloc(SizeT size) {
    data_ = alloc(size);
    size_ = size;
    fill_zero();
  }

protected:
  DataT data_;
  SizeT size_;

  DataT alloc(SizeT size) { return std::make_unique<DType[]>(size); }
};

}  // namespace odnn
