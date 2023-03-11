#pragma once

#include "odnn/tensor.h"

namespace odnn {
namespace nn {

template <typename DType>
Tensor<DType> conv2d(const Tensor<DType>& input, const Tensor<DType>& weight, const Tensor<DType>& bias);

}  // namespace nn

}  // namespace odnn
