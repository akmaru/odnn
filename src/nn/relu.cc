#include "odnn/nn/relu.h"

#include <glog/logging.h>

#include <cmath>
#include <ranges>

#include "odnn/tensor.h"

namespace odnn {
namespace nn {

template <typename DType>
Tensor<DType> relu(const Tensor<DType>& input) {
  Tensor<DType> output(input.shape());

  for (auto i : std::views::iota(0, output.num_of_elements())) {
    output[i] = std::max(input[i], static_cast<DType>(0));
  }

  return output;
}

template Tensor<float> relu(const Tensor<float>& input);

}  // namespace nn
}  // namespace odnn
