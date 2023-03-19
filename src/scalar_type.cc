#include <glog/logging.h>
#include <odnn/scalar_type.h>
#include <odnn/util.h>

#include "error.h"

namespace odnn {

SizeT byte_of_scalar_type(ScalarType dtype) {
  switch (dtype) {
    case ScalarType::kFloat32:
      return 4;
  }

  UNREACHABLE();
  return 0;
}

}  // namespace odnn
