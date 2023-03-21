#include "odnn/nn/batchnorm.h"

#include <gtest/gtest.h>
#include <odnn/tensor.h>
#include <torch/nn/functional/batchnorm.h>
#include <torch/nn/options/batchnorm.h>
#include <torch/torch.h>

#include "../util.h"

namespace odnn {
namespace nn {
namespace {

namespace F = torch::nn::functional;

TEST(BatchNorm2dTest, Float) {
  using DType = float;

  const SizeT batch = 1;
  const SizeT channel = 3;
  const SizeT width = 4;
  const SizeT height = 4;

  const Size input_shape = {batch, channel, height, width};
  const Size param_shape = {channel};

  auto x = Tensor<DType>::random(input_shape);
  auto mean = Tensor<DType>::random(param_shape);
  // For avoiding nan
  auto var = Tensor<DType>::filled(param_shape, 2.F);
  auto weight = Tensor<DType>::random(param_shape);
  auto bias = Tensor<DType>::random(param_shape);
  const DType eps = 1.0e-5;

  auto y = batchnorm2d(x, mean, var, BatchNorm2dOption<DType>().weight(weight).bias(bias).eps(eps));

  auto golden_x = testing::to_torch_tensor(x);
  auto golden_mean = testing::to_torch_tensor(mean);
  auto golden_var = testing::to_torch_tensor(var);
  auto golden_weight = testing::to_torch_tensor(weight);
  auto golden_bias = testing::to_torch_tensor(bias);
  auto golden_y = F::batch_norm(
      golden_x,
      golden_mean,
      golden_var,
      F::BatchNormFuncOptions().bias(golden_bias).weight(golden_weight).eps(eps)
  );

  testing::verify(y, golden_y);
}

}  // namespace
}  // namespace nn
}  // namespace odnn
