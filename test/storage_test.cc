#include "storage.h"

#include <gtest/gtest.h>

#include <algorithm>

namespace odnn {
namespace {

TEST(StorageTest, DefaultConstructor) {
  Storage s;
  EXPECT_EQ(s.data(), nullptr);
  EXPECT_EQ(s.bytes(), 0);
}

TEST(StorageTest, SizedConstructor) {
  Storage s(10);
  EXPECT_NE(s.data(), nullptr);
  EXPECT_EQ(s.bytes(), 10);
}

TEST(StorageTest, FillZeroFloat) {
  const auto size = 10;
  const auto bytes = size * sizeof(float);
  Storage s(bytes);
  s.fill_zero<float>();

  const auto* typed_ptr = reinterpret_cast<float*>(s.data());
  std::for_each_n(typed_ptr, size, [](float v) { EXPECT_FLOAT_EQ(v, 0.F); });
}

}  // namespace
}  // namespace odnn
