#include <gtest/gtest.h>
#include <odnn/nn/conv2d.h>
// #include <torch/torch.h>

#include "odnn/tensor.h"

namespace odnn {
namespace nn {
namespace {

TEST(Conv2dTest, Float) {
  using DType = float;

  const auto input_shape = Size({1, 3, 4, 4});
  const auto weight_shape = Size({5, 3, 3, 3});
  const auto bias_shape = Size({5});

  auto input = Tensor<DType>::zeros(input_shape);
  auto weight = Tensor<DType>::zeros(weight_shape);
  auto bias = Tensor<DType>::zeros(bias_shape);

  auto output = conv2d(input, weight, bias);
}

}  // namespace
}  // namespace nn
}  // namespace odnn
