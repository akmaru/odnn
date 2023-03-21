#include "odnn/nn/batchnorm.h"

#include <glog/logging.h>

#include <cmath>
#include <ranges>

#include "odnn/tensor.h"

namespace odnn {
namespace nn {

template <typename DType>
Tensor<DType> batchnorm2d(
    const Tensor<DType>& input,
    const Tensor<DType>& mean,
    const Tensor<DType>& var,
    const BatchNorm2dOption<DType>& option
) {
  CHECK_EQ(input.ndim(), 4);
  CHECK_EQ(mean.ndim(), 1);
  CHECK_EQ(var.ndim(), 1);

  const auto width = input.dim(3);
  const auto height = input.dim(2);
  const auto channel = input.dim(1);
  const auto batch = input.dim(0);

  CHECK_EQ(mean.dim(0), channel);
  CHECK_EQ(var.dim(0), channel);

  auto weight = option.weight();
  if (weight) {
    CHECK_EQ(weight.value().ndim(), 1);
    CHECK_EQ(weight.value().dim(0), channel);
  }

  auto bias = option.bias();
  if (bias) {
    CHECK_EQ(bias.value().ndim(), 1);
    CHECK_EQ(bias.value().dim(0), channel);
  }

  const Size output_shape({batch, channel, height, width});
  Tensor<DType> output(output_shape);

  for (auto b : std::views::iota(0, batch)) {
    for (auto c : std::views::iota(0, channel)) {
      for (auto y : std::views::iota(0, height)) {
        for (auto x : std::views::iota(0, width)) {
          const Size indices = {b, c, y, x};
          auto v = (input[indices] - mean[{c}]) / std::sqrt(var[{c}] + option.eps());

          if (weight) {
            v *= weight.value()[{c}];
          }

          if (bias) {
            v += bias.value()[{c}];
          }

          output[indices] = v;
        }
      }
    }
  }

  return output;
}

template Tensor<float> batchnorm2d(
    const Tensor<float>& input,
    const Tensor<float>& mean,
    const Tensor<float>& var,
    const BatchNorm2dOption<float>& option
);

}  // namespace nn
}  // namespace odnn
