#include "odnn/nn/conv2d.h"

#include <glog/logging.h>

#include <iostream>

#include "odnn/tensor.h"

namespace odnn {
namespace nn {

template <typename DType>
Tensor<DType> conv2d(
    const Tensor<DType>& input, const Tensor<DType>& weight, const Tensor<DType>& bias
) {
  CHECK_EQ(input.ndim(), 4);
  CHECK_EQ(weight.ndim(), 4);
  CHECK_EQ(bias.ndim(), 1);

  const auto width = input.dim(3);
  const auto height = input.dim(2);
  const auto input_channel = input.dim(1);
  const auto batch = input.dim(0);
  const auto output_channel = weight.dim(0);
  const auto kernel_height = weight.dim(2);
  const auto kernel_width = weight.dim(3);

  CHECK_EQ(weight.dim(1), input_channel);
  CHECK_EQ(bias.dim(0), output_channel);

  const Size output_shape({batch, output_channel, height, width});
  Tensor<DType> output(output_shape);

  for (auto b = decltype(batch)(0); b < batch; ++b) {
    for (auto oc = decltype(output_channel)(0); oc < output_channel; ++oc) {
      for (auto oy = decltype(height)(0); oy < height; ++oy) {
        for (auto ox = decltype(width)(0); ox < width; ++ox) {
          float sum = 0;

          for (auto ic = decltype(input_channel)(0); ic < input_channel; ++ic) {
            for (auto ky = decltype(kernel_height)(0); ky < kernel_height; ++ky) {
              for (auto kx = decltype(kernel_width)(0); kx < kernel_width; ++kx) {
                const auto ix = ox + kx - kernel_width / 2;
                const auto iy = oy + ky - kernel_height / 2;
                const Size i_indices({b, ic, iy, ix});
                const Size w_indices({oc, ic, ky, kx});

                // zero paddiong
                // TODO[(akmaru): Support more padding
                const auto iv = input.inbound(i_indices) ? input.at(i_indices) : 0;
                DVLOG(2) << "  (I" << i_indices.to_string() << " = " << iv << ") x ("
                         << "W" << w_indices.to_string() << " = " << weight.at(w_indices) << ")";

                sum += iv * weight.at(w_indices);
              }
            }
          }
          const Size o_indices({b, oc, oy, ox});
          output.at(o_indices) = sum + bias.at({oc});
          DVLOG(2) << "Output" << o_indices.to_string() << " := " << output.at(o_indices);
        }
      }
    }
  }

  return output;
}

template Tensor<float>
conv2d<float>(const Tensor<float>&, const Tensor<float>&, const Tensor<float>&);

}  // namespace nn

}  // namespace odnn
