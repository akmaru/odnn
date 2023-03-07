#pragma once

#include <odnn/util.h>

#include <cstddef>

#include "error.h"

namespace odnn {

enum class ScalarType { kFloat32 };

SizeT byte_of_scalar_type(ScalarType dtype);

}  // namespace odnn
