#pragma once

#include <array>
#include <cstddef>
#include <sstream>
#include <vector>

#include "log.h"

namespace odnn {

template <typename T>
class ArrayRef {
public:
  using size_type = std::size_t;

  using iterator = const T*;
  using const_iterator = const T*;
  using reverse_iterator = std::reverse_iterator<iterator>;

  ArrayRef() : data_(nullptr), length_(0) {}

  ArrayRef(const T* ptr, size_type length) : data_(ptr), length_(length) {}

  explicit ArrayRef(const T& one_elem) : data_(&one_elem), length_(1) {}

  template <std::size_t N>
  ArrayRef(const std::array<T, N>& arr) : data_(arr.data()), length_(N) {}

  ArrayRef(const std::vector<T>& vec) : data_(vec.data()), length_(vec.size()) {}

  ArrayRef(const std::initializer_list<T>& init)
      : data_(std::begin(init) == std::end(init) ? nullptr : std::begin(init)), length_(init.size()) {}

  inline const T* data() const { return data_; }
  inline size_type size() const { return length_; }

  iterator begin() const { return data(); }
  iterator end() const { return data() + size(); }

  const_iterator cbegin() const { return data(); }
  const_iterator cend() const { return data() + size(); }

  reverse_iterator rbegin() const { return reverse_iterator(end()); }
  reverse_iterator rend() const { return reverse_iterator(begin()); }

  bool empty() const { return size() == 0; }

  const T& operator[](size_type index) const { return data()[index]; }

  const T& at(size_type index) const {
    CHECK_LT(index, size());
    return data()[index];
  }

  std::string to_string() const {
    std::ostringstream oss;
    oss << "[";
    std::size_t i = 0;

    for (const auto& v : *this) {
      if (i++ > 0) {
        oss << ", ";
      }
      oss << v;
    }

    oss << "]";
    return oss.str();
  }

  std::vector<T> to_vector() const { return std::vector<T>(data_, data_ + length_); }

private:
  const T* data_;
  size_type length_;
};

template <typename T>
std::ostream& operator<<(std::ostream& out, ArrayRef<T> ref) {
  out << ref.to_string();
  return out;
}

}  // namespace odnn
