#include <gtest/gtest.h>
#include <hello.h>

namespace odnn {
namespace {

TEST(HelloTest, Hello) { EXPECT_EQ("Hello", hello()); }

}  // namespace
}  // namespace odnn
