#pragma once

#include <odnn/tensor.h>
#include <odnn/typedef.h>

#include <array>
#include <optional>

#include "builder.h"

namespace odnn {
namespace nn {

template <typename DType>
struct Conv2dOption {
  static constexpr std::size_t kDim = 2;

  ODNN_BUILDER_OPTIONAL_FIELD(Tensor<DType>, bias);
};

template <typename DType>
Tensor<DType> conv2d(
    const Tensor<DType>& input, const Tensor<DType>& weight, const Conv2dOption<DType>& option
);

}  // namespace nn

}  // namespace odnn
