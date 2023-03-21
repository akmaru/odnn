#include "odnn/tensor.h"

#include <ostream>
#include <ranges>
#include <vector>

namespace odnn {

template <typename DType>
std::string Tensor<DType>::to_string_in_dim(SizeT dim_index, const std::vector<SizeT>& shape)
    const {
  std::ostringstream oss;
  oss << "[";

  for (const auto i : std::views::iota(0, dim(dim_index))) {
    auto new_shape = shape;
    new_shape.push_back(i);

    if (dim_index == ndim() - 1) {
      oss << this->operator[](new_shape);
    } else {
      // Insert head indent
      if (i > 0) {
        for (auto _ : std::views::iota(0, dim_index + 1)) {
          oss << " ";
        }
      }
      oss << to_string_in_dim(dim_index + 1, new_shape);
    }

    if (i < dim(dim_index) - 1) {
      oss << ", ";
      if (dim_index < ndim() - 1) {
        oss << "\n";
      }
    }
  }

  oss << "]";
  return oss.str();
}

template <typename DType>
std::ostream& operator<<(std::ostream& out, Tensor<DType> tensor) {
  out << tensor.to_string();
  return out;
}

template class Tensor<float>;

}  // namespace odnn
