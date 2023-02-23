#include "odnn/size.h"

#include <gtest/gtest.h>

#include <array>
#include <vector>

namespace odnn {
namespace {

TEST(SizeTest, Basic) {
  const Size size({1, 3, 224, 224});

  EXPECT_EQ(size[0], 1);
  EXPECT_EQ(size[1], 3);
  EXPECT_EQ(size[2], 224);
  EXPECT_EQ(size[3], 224);
  EXPECT_EQ(size.size(), 4);
}

TEST(SizeTest, Stride) {
  const Size size({1, 3, 224, 224});
  const auto strides = size.strides();

  EXPECT_EQ(strides[0], 1 * 3 * 224 * 224);
  EXPECT_EQ(strides[1], 3 * 224 * 224);
  EXPECT_EQ(strides[2], 224 * 224);
  EXPECT_EQ(strides[3], 224);
  EXPECT_EQ(strides.size(), 4);
}

}  // namespace
}  // namespace odnn
