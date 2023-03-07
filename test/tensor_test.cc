#include "odnn/tensor.h"

#include <gtest/gtest.h>

#include "odnn/size.h"

namespace odnn {
namespace {

TEST(TensorTest, Zeros) {
  const auto shape = Size({1, 2});
  auto tensor = Tensor::zeros(shape);
  const auto elems = shape.num_of_elements();
  for (auto i = static_cast<decltype(elems)>(0); i < elems; ++i) {
    EXPECT_FLOAT_EQ(0.F, tensor.at<float>(i));
  }
}

TEST(TensorTest, At) {
  auto tensor = Tensor::zeros({1, 2});
  EXPECT_FLOAT_EQ(0.F, tensor.at<float>({0, 0}));
  tensor.at<float>({0, 1}) = 1.F;
  EXPECT_FLOAT_EQ(1.F, tensor.at<float>({0, 1}));
}

}  // namespace
}  // namespace odnn
