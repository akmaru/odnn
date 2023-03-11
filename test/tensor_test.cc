#include "odnn/tensor.h"

#include <gtest/gtest.h>

#include "odnn/size.h"

namespace odnn {
namespace {

TEST(TensorTest, At) {
  using DType = float;
  auto tensor = Tensor<DType>::zeros({1, 2});
  EXPECT_FLOAT_EQ(0.F, tensor.at({0, 0}));
  tensor.at({0, 1}) = 1.F;
  EXPECT_FLOAT_EQ(1.F, tensor.at({0, 1}));
}

}  // namespace
}  // namespace odnn
