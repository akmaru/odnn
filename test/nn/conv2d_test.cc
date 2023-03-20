#include <gtest/gtest.h>
#include <odnn/nn/conv2d.h>
#include <torch/nn/options/conv.h>
#include <torch/torch.h>

#include "../util.h"
#include "odnn/tensor.h"

namespace odnn {
namespace nn {
namespace {

namespace F = torch::nn::functional;

TEST(Conv2dTest, Float) {
  using DType = float;

  const SizeT batch = 1;
  const SizeT input_channel = 3;
  const SizeT output_channel = 5;
  const SizeT width = 4;
  const SizeT height = 4;
  const SizeT kernel_size = 3;

  const Size input_shape = {batch, input_channel, height, width};
  const Size weight_shape = {output_channel, input_channel, kernel_size, kernel_size};
  const Size bias_shape = {output_channel};

  auto x = Tensor<DType>::random(input_shape);
  auto weight = Tensor<DType>::random(weight_shape);
  auto bias = Tensor<DType>::random(bias_shape);

  auto y = conv2d(x, weight, bias);

  auto golden_x = testing::to_torch_tensor(x);
  auto golden_weight = testing::to_torch_tensor(weight);
  auto golden_bias = testing::to_torch_tensor(bias);
  auto golden_y = F::detail::conv2d(golden_x, golden_weight, golden_bias, 1, 1, 1, 1);

  testing::verify(y, golden_y);
}

}  // namespace
}  // namespace nn
}  // namespace odnn
