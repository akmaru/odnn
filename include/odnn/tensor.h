#pragma once

#include <cstddef>
#include <cstdint>
#include <memory>
#include <numeric>
#include <vector>

#include "array_ref.h"
#include "odnn/scalar_type.h"
#include "odnn/size.h"

namespace odnn {

class Tensor {
  using ElemT = ScalarType;
  using DataT = std::uint8_t[];
  using DataRefT = std::shared_ptr<DataT>;

public:
  Tensor() : shape_(), dtype_(ScalarType::kFloat32), data_ref_(nullptr) {}
  Tensor(const Size& shape, ScalarType dtype = ScalarType::kFloat32)
      : shape_(shape), dtype_(dtype), data_ref_(zero_data(shape, dtype)) {}

  Size shape() const noexcept { return shape_; }

  ElemT dtype() const noexcept { return dtype_; }

  template <typename DType>
  DType& at(Size::IndexT index) {
    CHECK_LE(index, num_of_elements());
    const auto data = data_ref_.get();
    return reinterpret_cast<DType*>(data)[index];
  }

  template <typename DType>
  DType& at(SizeRef indices) {
    CHECK(shape().inbound(indices));
    const auto flatten_index = flatten_index_from_indices(indices);
    return at<DType>(flatten_index);
  }

  template <typename DType>
  const DType& at(Size::IndexT index) const {
    CHECK_LE(index, num_of_elements());
    const auto data = data_ref_.get();
    return reinterpret_cast<DType*>(data)[index];
  }

  template <typename DType>
  const DType& at(SizeRef indices) const {
    CHECK(shape().inbound(indices));
    const auto flatten_index = flatten_index_from_indices(indices);
    return at<DType>(flatten_index);
  }

  Size::IndexT num_of_elements() const noexcept { return shape_.num_of_elements(); }

  static Tensor zeros(SizeRef shape, ScalarType dtype = ScalarType::kFloat32) { return Tensor(shape, dtype); }

protected:
  Size shape_;
  ElemT dtype_;
  DataRefT data_ref_;

  Size::IndexT flatten_index_from_indices(SizeRef indices) const {
    CHECK_EQ(indices.size(), shape_.size());

    return std::inner_product(indices.begin(), indices.end(), shape_.strides().begin(), 0);
  }

  static DataRefT zero_data(const Size& shape, ScalarType dtype) {
    const auto byte = shape.num_of_elements() * byte_of_scalar_type(dtype);
    DataRefT data_ref(new std::uint8_t[byte]);
    return data_ref;
  }
};

}  // namespace odnn
