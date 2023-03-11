#include "storage.h"

#include <gtest/gtest.h>

#include <algorithm>

namespace odnn {
namespace {

TEST(StorageTest, DefaultConstructor) {
  Storage<float> s;
  EXPECT_EQ(s.data(), nullptr);
  EXPECT_EQ(s.bytes(), 0);
}

TEST(StorageTest, SizedConstructor) {
  using DType = float;
  const auto size = 10;
  Storage<DType> s(size);
  EXPECT_NE(s.data(), nullptr);
  EXPECT_EQ(s.size(), size);
  EXPECT_EQ(s.bytes(), size * sizeof(DType));
  std::for_each_n(s.data(), size, [](DType v) { EXPECT_FLOAT_EQ(v, 0.F); });
}

}  // namespace
}  // namespace odnn
