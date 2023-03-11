#include "odnn/tensor.h"

#include <gtest/gtest.h>

#include <ranges>

#include "odnn/size.h"

namespace odnn {
namespace {

TEST(TensorTest, Zeros) {
  using DType = float;
  const Size shape({2, 3});
  auto tensor = Tensor<DType>::zeros(shape);

  EXPECT_EQ(tensor.ndim(), shape.ndim());

  const auto dim_range = std::ranges::iota_view(0, tensor.ndim());
  std::ranges::for_each(dim_range, [&](auto i) { EXPECT_EQ(tensor.dim(i), shape[i]); });

  std::for_each(tensor.begin(), tensor.end(), [](DType v) { EXPECT_FLOAT_EQ(v, 0.F); });
}

TEST(TensorTest, At) {
  using DType = float;
  auto tensor = Tensor<DType>::zeros({1, 2});
  EXPECT_FLOAT_EQ(0.F, tensor.at({0, 0}));
  tensor.at({0, 1}) = 1.F;
  EXPECT_FLOAT_EQ(1.F, tensor.at({0, 1}));
}

}  // namespace
}  // namespace odnn
