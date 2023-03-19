#pragma once

#include <glog/logging.h>

namespace odnn {

#define UNIMPLENTED() LOG_IF(FATAL, true) << "Not implemented"
#define UNREACHABLE() LOG_IF(FATAL, true) << "Entered unreachable code"

}  // namespace odnn
