#include "odnn/size.h"

#include <ostream>

namespace odnn {

std::ostream& operator<<(std::ostream& out, const Size& size) {
  out << size.to_string();
  return out;
}

}  // namespace odnn
