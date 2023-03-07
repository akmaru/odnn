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

class Tensor {
  using ElemT = ScalarType;
  using DataT = std::uint8_t[];
  using DataPtrT = std::uint8_t*;
  using StoragePtrT = std::shared_ptr<Storage>;

public:
  Tensor() : dtype_(ScalarType::kFloat32) {}
  explicit Tensor(const Size& shape, ScalarType dtype = ScalarType::kFloat32)
      : shape_(shape), dtype_(dtype), storage_(std::make_shared<Storage>()) {
    const auto bytes = shape.num_of_elements() * byte_of_scalar_type(dtype);
    storage_->alloc(bytes);
  }

  inline Storage* storage() noexcept { return storage_.get(); }

  inline const Storage* storage() const noexcept { return storage_.get(); }

  inline Size shape() const noexcept { return shape_; }

  inline ElemT dtype() const noexcept { return dtype_; }

  template <typename DType>
  DType& at(SizeT index) {
    CHECK_LE(index, num_of_elements());
    return storage()->at<DType>(index);
  }

  template <typename DType>
  DType& at(SizeRef indices) {
    CHECK(shape().inbound(indices));
    const auto flatten_index = flatten_index_from_indices(indices);
    return at<DType>(flatten_index);
  }

  template <typename DType>
  const DType& at(SizeT index) const {
    CHECK_LE(index, num_of_elements());
    return storage()->at<DType>(index);
  }

  template <typename DType>
  const DType& at(SizeRef indices) const {
    CHECK(shape().inbound(indices));
    const auto flatten_index = flatten_index_from_indices(indices);
    return at<DType>(flatten_index);
  }

  auto dim(SizeT index) const {
    CHECK_LE(index, shape().size());
    return shape()[index];
  }

  SizeT num_of_dims() const noexcept { return shape().size(); }

  SizeT num_of_elements() const noexcept { return shape_.num_of_elements(); }

  static Tensor zeros(SizeRef shape, ScalarType dtype = ScalarType::kFloat32) {
    auto tensor = Tensor(shape, dtype);
    tensor.fill_zero();
    return tensor;
  }

protected:
  Size shape_;
  ElemT dtype_;
  StoragePtrT storage_;

  SizeT flatten_index_from_indices(SizeRef indices) const {
    CHECK_EQ(static_cast<SizeT>(indices.size()), shape_.size());

    return std::inner_product(indices.begin(), indices.end(), shape_.strides().begin(), static_cast<SizeT>(0));
  }

  void fill_zero() { storage_->fill_zero<float>(); }
};

}  // namespace odnn
