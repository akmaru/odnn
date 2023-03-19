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
#include "random.h"
#include "storage.h"

namespace odnn {

template <typename DType>
class Tensor {
public:
  using StorageT = Storage<DType>;
  using StoragePtrT = std::shared_ptr<StorageT>;

  using iterator = DType*;
  using const_iterator = const DType*;
  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  Tensor() = default;

  explicit Tensor(const Size& shape) : shape_(shape), storage_(std::make_shared<StorageT>()) {
    const auto size = shape.num_of_elements();
    storage_->calloc(size);
  }

  StorageT* storage() noexcept { return storage_.get(); }

  const StorageT* storage() const noexcept { return storage_.get(); }

  const Size& shape() const noexcept { return shape_; }

  bool inbound(SizeRef indices) const noexcept { return shape().inbound(indices); }

  SizeT flatten_index(SizeRef indices) const {
    CHECK_EQ(static_cast<SizeT>(indices.size()), shape_.ndim());
    return std::inner_product(
        indices.begin(), indices.end(), shape_.strides().begin(), static_cast<SizeT>(0)
    );
  }

  DType& at(SizeRef indices) {
    CHECK(inbound(indices));
    const auto fi = flatten_index(indices);
    return storage()->operator[](fi);
  }

  const DType& at(SizeRef indices) const {
    CHECK(inbound(indices));
    const auto fi = flatten_index(indices);
    return storage()->operator[](fi);
  }

  auto dim(SizeT index) const {
    CHECK_LE(index, shape().ndim());
    return shape()[index];
  }

  SizeT ndim() const noexcept { return shape().ndim(); }

  SizeT num_of_elements() const noexcept { return shape_.num_of_elements(); }

  iterator begin() noexcept { return storage()->begin(); }
  iterator end() noexcept { return storage()->end(); }

  const_iterator cbegin() const noexcept { return storage()->cbegin(); }
  const_iterator cend() const noexcept { return storage()->cend(); }

  reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
  reverse_iterator rend() noexcept { return reverse_iterator(begin()); }

  const_reverse_iterator crbegin() const noexcept { return const_reverse_iterator(cend()); }
  const_reverse_iterator crend() const noexcept { return const_reverse_iterator(cbegin()); }

  static Tensor zeros(SizeRef shape) {
    auto tensor = Tensor<DType>(shape);
    return tensor;
  }

  static Tensor filled(SizeRef shape, DType value) {
    auto tensor = Tensor<DType>(shape);
    tensor.storage()->fill(value);
    return tensor;
  }

  static Tensor random(SizeRef shape) {
    auto tensor = Tensor<DType>(shape);
    std::for_each(tensor.begin(), tensor.end(), [](auto& v) mutable { v = random_value<DType>(); });
    return tensor;
  }

  static Tensor sequence(SizeRef shape) {
    auto tensor = Tensor<DType>(shape);
    tensor.storage()->fill_sequence();
    return tensor;
  }

protected:
  Size shape_;
  StoragePtrT storage_;

  void fill_zero() { storage().fill_zero(); }
};

}  // namespace odnn
