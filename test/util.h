#pragma once

#include <glog/logging.h>
#include <odnn/tensor.h>
#include <torch/torch.h>

#include <algorithm>
#include <ranges>

namespace odnn {
namespace testing {

namespace {

template <typename T>
torch::Tensor to_torch_tensor(const Tensor<T>& src) {
  auto* data = reinterpret_cast<void*>(const_cast<T*>(src.storage()->data()));
  auto shape = static_cast<SizeRef>(src.shape()).to_vector();
  // TODO(akmaru): Hundle type
  auto options = torch::TensorOptions().dtype(torch::kFloat32);
  auto dst = torch::from_blob(data, shape, options).to(torch::kFloat32).clone();

  return dst;
}

template <typename T>
void verify(const Tensor<T>& own, const torch::Tensor& golden) {
  const auto own_data = own.storage()->data();
  const auto golden_data = golden.data_ptr<T>();
  EXPECT_EQ(own.num_of_elements(), golden.numel());

  const auto index_range = std::ranges::iota_view(0, own.num_of_elements());
  std::ranges::for_each(index_range, [&](auto i) {
    EXPECT_NEAR(own_data[i], golden_data[i], 10e-2);
  });
}

}  // namespace

}  // namespace testing
}  // namespace odnn
