#pragma once

#include <glog/logging.h>
#include <odnn/util.h>

#include <cstddef>

namespace odnn {

enum class ScalarType { kFloat32 };

SizeT byte_of_scalar_type(ScalarType dtype);

}  // namespace odnn
