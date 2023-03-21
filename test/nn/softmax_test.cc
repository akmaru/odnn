#include "odnn/nn/softmax.h"

#include <gtest/gtest.h>
#include <odnn/tensor.h>
#include <torch/nn/functional/activation.h>
#include <torch/torch.h>

#include "../util.h"

namespace odnn {
namespace nn {
namespace {

namespace F = torch::nn::functional;

TEST(SoftmaxTest, Float) {
  using DType = float;

  const SizeT batch = 1;
  const SizeT features = 4;

  const Size input_shape = {batch, features};

  auto x = Tensor<DType>::random(input_shape);
  auto y = softmax(x);

  auto golden_x = testing::to_torch_tensor(x);
  auto golden_y = F::softmax(golden_x, F::SoftmaxFuncOptions(1));

  testing::verify(y, golden_y);
}

}  // namespace
}  // namespace nn
}  // namespace odnn
