#include "array_ref.h"

#include <ostream>

namespace odnn {

template <typename T>
std::ostream& operator<<(std::ostream& out, ArrayRef<T> ref) {
  out << ref.to_string();
  return out;
}

}  // namespace odnn
