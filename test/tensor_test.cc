#include "odnn/tensor.h"

#include <gtest/gtest.h>

namespace odnn {
namespace {

TEST(TensorTest, At) {
  // const std::vector<std::int64_t> shape = {2, 3};
  // auto tensor = Tensor::zeros(shape);
  auto tensor = Tensor::zeros({1, 2});
  EXPECT_EQ(0.f, tensor.at<float>({0, 0}));
  tensor.at<float>({0, 1}) = 1.f;
  EXPECT_EQ(1.f, tensor.at<float>({0, 1}));
}

}  // namespace
}  // namespace odnn
