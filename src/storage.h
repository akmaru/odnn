#pragma once

#include <odnn/util.h>

#include <algorithm>
#include <cstdint>
#include <memory>

#include "error.h"

namespace odnn {

template <typename DType>
class Storage {
public:
  using DataT = std::unique_ptr<DType[]>;

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

  void realloc(SizeT size) {
    data_ = alloc(size);
    size_ = size;
  }

  void fill_zero() { std::fill(data(), data() + size(), static_cast<DType>(0)); }

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
