#include "odnn/nn/relu.h"

#include <gtest/gtest.h>
#include <odnn/tensor.h>
#include <torch/nn/functional/activation.h>
#include <torch/nn/functional/batchnorm.h>
#include <torch/nn/options/batchnorm.h>
#include <torch/torch.h>

#include "../util.h"

namespace odnn {
namespace nn {
namespace {

namespace F = torch::nn::functional;

TEST(ReLUTest, Float) {
  using DType = float;

  const SizeT batch = 1;
  const SizeT channel = 3;
  const SizeT width = 4;
  const SizeT height = 4;

  const Size input_shape = {batch, channel, height, width};

  auto x = Tensor<DType>::random(input_shape);
  auto y = relu(x);

  auto golden_x = testing::to_torch_tensor(x);
  auto golden_y = F::relu(golden_x);

  testing::verify(y, golden_y);
}

}  // namespace
}  // namespace nn
}  // namespace odnn
