#include "odnn/size.h"

#include <glog/logging.h>
#include <gtest/gtest.h>

#include <array>
#include <vector>

namespace odnn {
namespace {

TEST(SizeTest, FromArrayRef) {
  const Size size({1, 3, 224, 224});

  EXPECT_EQ(size[0], 1);
  EXPECT_EQ(size[1], 3);
  EXPECT_EQ(size[2], 224);
  EXPECT_EQ(size[3], 224);
  EXPECT_EQ(size.ndim(), 4);
  EXPECT_EQ(size.num_of_elements(), 1 * 3 * 224 * 224);

  EXPECT_TRUE(size.inbound({0, 0, 0, 0}));
  EXPECT_FALSE(size.inbound({0, 2, 223, 224}));
  EXPECT_FALSE(size.inbound({0, 2, 224, 223}));
  EXPECT_FALSE(size.inbound({0, 3, 223, 223}));
  EXPECT_FALSE(size.inbound({1, 2, 223, 223}));
  EXPECT_FALSE(size.inbound({0}));
}

TEST(SizeTest, FromInit) {
  const Size size = {1, 3, 224, 224};

  EXPECT_EQ(size[0], 1);
  EXPECT_EQ(size[1], 3);
  EXPECT_EQ(size[2], 224);
  EXPECT_EQ(size[3], 224);
  EXPECT_EQ(size.ndim(), 4);
  EXPECT_EQ(size.num_of_elements(), 1 * 3 * 224 * 224);

  EXPECT_TRUE(size.inbound({0, 0, 0, 0}));
  EXPECT_FALSE(size.inbound({0, 2, 223, 224}));
  EXPECT_FALSE(size.inbound({0, 2, 224, 223}));
  EXPECT_FALSE(size.inbound({0, 3, 223, 223}));
  EXPECT_FALSE(size.inbound({1, 2, 223, 223}));
  EXPECT_FALSE(size.inbound({0}));
}

TEST(SizeTest, Stride) {
  const Size size({1, 3, 224, 224});
  const auto strides = size.strides();

  EXPECT_EQ(strides[0], size[1] * size[2] * size[3]);
  EXPECT_EQ(strides[1], size[2] * size[3]);
  EXPECT_EQ(strides[2], size[3]);
  EXPECT_EQ(strides[3], 1);
  EXPECT_EQ(strides.ndim(), 4);
}

}  // namespace
}  // namespace odnn
