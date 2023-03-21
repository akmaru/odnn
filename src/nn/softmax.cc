#include "odnn/nn/softmax.h"

#include <glog/logging.h>

#include <cmath>
#include <ranges>

#include "odnn/tensor.h"

namespace odnn {
namespace nn {

template <typename DType>
Tensor<DType> softmax(const Tensor<DType>& input) {
  // Assuming input.nsim() == 2 and computing dim = 1;
  CHECK_EQ(input.ndim(), 2);

  const auto batch = input.dim(0);
  const auto features = input.dim(1);

  Tensor<DType> output(input.shape());

  for (auto b : std::views::iota(0, batch)) {
    DType sum = 0;
    for (auto c : std::views::iota(0, features)) {
      sum += std::exp(input[{b, c}]);
    }

    for (auto c : std::views::iota(0, features)) {
      output[{b, c}] = std::exp(input[{b, c}]) / sum;
    }
  }

  return output;
}

template Tensor<float> softmax(const Tensor<float>& input);

}  // namespace nn
}  // namespace odnn
