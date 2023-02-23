#include "array_ref.h"

#include <gtest/gtest.h>

#include <array>
#include <vector>

namespace odnn {
namespace {

using T = int;
constexpr std::size_t size = 5;

void test_for_by_index(const ArrayRef<T>& ref) {
  for (auto i = decltype(ref.size())(0); i < ref.size(); ++i) {
    EXPECT_EQ(ref[i], i);
  }
}

void test_for_by_iter(const ArrayRef<T>& ref) {
  auto i = 0;
  for (auto it = ref.begin(); it != ref.end(); ++it) {
    EXPECT_EQ(*it, i);
    i += 1;
  }
}

void test_for_by_citer(const ArrayRef<T>& ref) {
  auto i = 0;
  for (auto it = ref.cbegin(); it != ref.cend(); ++it) {
    EXPECT_EQ(*it, i);
    i += 1;
  }
}

void test_for_by_riter(const ArrayRef<T>& ref) {
  auto i = ref.size() - 1;
  for (auto it = ref.rbegin(); it != ref.rend(); ++it) {
    EXPECT_EQ(*it, i);
    i -= 1;
  }
}

void array_ref_test(const ArrayRef<T>& ref) {
  test_for_by_index(ref);
  test_for_by_iter(ref);
  test_for_by_citer(ref);
  test_for_by_riter(ref);

  EXPECT_EQ(ref.size(), size);

  EXPECT_EQ(ref.to_string(), "[0, 1, 2, 3, 4]");
}

TEST(ArrayRefTest, FromOneElem) {
  const int v = 1;
  auto ref = static_cast<ArrayRef<T>>(v);
  EXPECT_EQ(ref[0], 1);
  EXPECT_EQ(ref.size(), 1);
  EXPECT_EQ(ref.to_string(), "[1]");
}

TEST(ArrayRefTest, FromArray) {
  const std::array<T, size> arr = {0, 1, 2, 3, 4};
  array_ref_test(arr);
}

TEST(ArrayRefTest, FromVector) {
  const std::vector<T> vec = {0, 1, 2, 3, 4};
  array_ref_test(vec);
}

TEST(ArrayRefTest, FromInit) { array_ref_test({0, 1, 2, 3, 4}); }

}  // namespace
}  // namespace odnn
