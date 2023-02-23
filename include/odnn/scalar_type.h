#pragma once

#include <cstddef>

#include "error.h"

namespace odnn {

enum class ScalarType { kFloat32 };

std::size_t byte_of_scalar_type(ScalarType dtype) {
  switch (dtype) {
    case ScalarType::kFloat32:
      return 4Uz;
  }

  UNREACHABLE();
  return 0;
}

}  // namespace odnn
