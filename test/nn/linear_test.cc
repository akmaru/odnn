#include <gtest/gtest.h>
#include <odnn/nn/linear.h>
#include <torch/nn/functional/linear.h>
#include <torch/torch.h>

#include "../util.h"
#include "odnn/tensor.h"

namespace odnn {
namespace nn {
namespace {

namespace F = torch::nn::functional;

TEST(LinearTest, Float) {
  using DType = float;

  const SizeT batch = 1;
  const SizeT in_feature = 3;
  const SizeT out_feature = 5;

  const Size input_shape = {batch, in_feature};
  const Size weight_shape = {out_feature, in_feature};
  const Size bias_shape = {out_feature};

  auto x = Tensor<DType>::random(input_shape);
  auto weight = Tensor<DType>::random(weight_shape);
  auto bias = Tensor<DType>::random(bias_shape);

  auto y = linear(x, weight, LinearOption<DType>().bias(bias));

  auto golden_x = testing::to_torch_tensor(x);
  auto golden_weight = testing::to_torch_tensor(weight);
  auto golden_bias = testing::to_torch_tensor(bias);
  auto golden_y = F::linear(golden_x, golden_weight, golden_bias);

  testing::verify(y, golden_y);
}

}  // namespace
}  // namespace nn
}  // namespace odnn
