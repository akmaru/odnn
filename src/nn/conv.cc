#include "odnn/nn/conv.h"

#include <glog/logging.h>

#include <ranges>

#include "odnn/tensor.h"

namespace odnn {
namespace nn {

template <typename DType>
Tensor<DType> conv2d(
    const Tensor<DType>& input, const Tensor<DType>& weight, const Conv2dOption<DType>& option
) {
  CHECK_EQ(input.ndim(), 4);
  CHECK_EQ(weight.ndim(), 4);

  const auto width = input.dim(3);
  const auto height = input.dim(2);
  const auto input_channel = input.dim(1);
  const auto batch = input.dim(0);
  const auto output_channel = weight.dim(0);
  const auto kernel_height = weight.dim(2);
  const auto kernel_width = weight.dim(3);

  CHECK_EQ(weight.dim(1), input_channel);

  auto bias = option.bias();
  if (bias) {
    CHECK_EQ(bias.value().ndim(), 1);
    CHECK_EQ(bias.value().dim(0), output_channel);
  }

  // TODO(akmaru) Support padding and stride parameter
  // We support only case of input_shape == output_shape now"
  const Size output_shape({batch, output_channel, height, width});
  Tensor<DType> output(output_shape);

  for (auto b : std::views::iota(0, batch)) {
    for (auto oc : std::views::iota(0, output_channel)) {
      for (auto oy : std::views::iota(0, height)) {
        for (auto ox : std::views::iota(0, width)) {
          DType sum = 0;

          for (auto ic : std::views::iota(0, input_channel)) {
            for (auto ky : std::views::iota(0, kernel_height)) {
              for (auto kx : std::views::iota(0, kernel_width)) {
                const auto ix = ox + kx - kernel_width / 2;
                const auto iy = oy + ky - kernel_height / 2;
                const Size i_indices = {b, ic, iy, ix};
                const Size w_indices = {oc, ic, ky, kx};

                // zero paddiong
                // TODO(akmaru): Support more padding
                const auto iv = input.inbound(i_indices) ? input[i_indices] : 0;
                DVLOG(2) << "  (I" << i_indices.to_string() << " = " << iv << ") x ("
                         << "W" << w_indices.to_string() << " = " << weight[w_indices] << ")";

                sum += iv * weight[w_indices];
              }
            }
          }

          // If any, add bias
          if (bias) {
            sum += bias.value()[{oc}];
          }

          const Size o_indices({b, oc, oy, ox});
          output[o_indices] = sum;

          DVLOG(2) << "Output" << o_indices.to_string() << " := " << output[o_indices];
        }
      }
    }
  }

  return output;
}

template Tensor<float>
conv2d<float>(const Tensor<float>&, const Tensor<float>&, const Conv2dOption<float>&);

}  // namespace nn
}  // namespace odnn
