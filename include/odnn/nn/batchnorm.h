#pragma once

#include <odnn/tensor.h>
#include <odnn/typedef.h>

#include <array>
#include <optional>

#include "builder.h"

namespace odnn {
namespace nn {

template <typename DType>
struct BatchNorm2dOption {
  static constexpr std::size_t kDim = 2;

  ODNN_BUILDER_OPTIONAL_FIELD(Tensor<DType>, weight);
  ODNN_BUILDER_OPTIONAL_FIELD(Tensor<DType>, bias);
  ODNN_BUILDER_FIELD(DType, eps) = 1.0e-5;
};

template <typename DType>
Tensor<DType> batchnorm2d(
    const Tensor<DType>& input,
    const Tensor<DType>& mean,
    const Tensor<DType>& var,
    const BatchNorm2dOption<DType>& option
);

}  // namespace nn
}  // namespace odnn
