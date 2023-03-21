#pragma once

#include <odnn/tensor.h>
#include <odnn/typedef.h>

#include <array>
#include <optional>

#include "builder.h"

namespace odnn {
namespace nn {

template <typename DType>
Tensor<DType> softmax(const Tensor<DType>& input);

}  // namespace nn
}  // namespace odnn
