#include "odnn/nn/linear.h"

#include <glog/logging.h>

#include <ranges>

#include "odnn/tensor.h"

namespace odnn {
namespace nn {

template <typename DType>
Tensor<DType> linear(
    const Tensor<DType>& input, const Tensor<DType>& weight, const LinearOption<DType>& option
) {
  CHECK_EQ(input.ndim(), 2);
  CHECK_EQ(weight.ndim(), 2);

  const auto batch = input.dim(0);
  const auto in_features = input.dim(1);
  const auto out_features = weight.dim(0);

  CHECK_EQ(weight.dim(1), in_features);

  auto bias = option.bias();
  if (bias) {
    CHECK_EQ(bias.value().ndim(), 1);
    CHECK_EQ(bias.value().dim(0), out_features);
  }

  const Size output_shape({batch, out_features});
  Tensor<DType> output(output_shape);

  for (auto b : std::views::iota(0, batch)) {
    for (auto oc : std::views::iota(0, out_features)) {
      DType sum = 0;

      for (auto ic : std::views::iota(0, in_features)) {
        const Size i_indices = {b, ic};
        const Size w_indices = {oc, ic};

        sum += input[i_indices] * weight[w_indices];
      }

      // If any, add bias
      if (bias) {
        sum += bias.value()[{oc}];
      }

      const Size o_indices({b, oc});
      output[o_indices] = sum;

      DVLOG(2) << "Output" << o_indices.to_string() << " := " << output[o_indices];
    }
  }

  return output;
}

template Tensor<float>
linear<float>(const Tensor<float>&, const Tensor<float>&, const LinearOption<float>&);

}  // namespace nn
}  // namespace odnn
