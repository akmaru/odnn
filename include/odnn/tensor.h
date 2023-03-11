#pragma once

#include <odnn/scalar_type.h>
#include <odnn/size.h>
#include <odnn/util.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <numeric>
#include <ranges>
#include <vector>

#include "array_ref.h"
#include "storage.h"

namespace odnn {

template <typename DType>
class Tensor {
  using StorageT = Storage<DType>;
  using StoragePtrT = std::shared_ptr<StorageT>;

public:
  Tensor() = default;

  explicit Tensor(const Size& shape) : shape_(shape), storage_(std::make_shared<StorageT>()) {
    const auto size = shape.num_of_elements();
    storage_->calloc(size);
  }

  StorageT* storage() noexcept { return storage_.get(); }

  const StorageT* storage() const noexcept { return storage_.get(); }

  Size shape() const noexcept { return shape_; }

  DType& at(SizeRef indices) {
    CHECK(shape().inbound(indices));
    const auto fi = flatten_index(indices);
    return storage()->operator[](fi);
  }

  const DType& at(SizeRef indices) const {
    CHECK(shape().inbound(indices));
    const auto fi = flatten_index(indices);
    return storage()->operator[](fi);
  }

  auto dim(SizeT index) const {
    CHECK_LE(index, shape().size());
    return shape()[index];
  }

  SizeT num_of_dims() const noexcept { return shape().size(); }

  SizeT num_of_elements() const noexcept { return shape_.num_of_elements(); }

  static Tensor zeros(SizeRef shape) {
    auto tensor = Tensor<DType>(shape);
    return tensor;
  }

protected:
  Size shape_;
  StoragePtrT storage_;

  SizeT flatten_index(SizeRef indices) const {
    CHECK_EQ(static_cast<SizeT>(indices.size()), shape_.size());

    return std::inner_product(indices.begin(), indices.end(), shape_.strides().begin(), static_cast<SizeT>(0));
  }

  void fill_zero() { storage().fill_zero(); }
};

}  // namespace odnn
