#pragma once

#include <odnn/util.h>

#include <algorithm>
#include <cstdint>
#include <memory>

#include "error.h"

namespace odnn {

class Storage {
public:
  using DataPtrT = std::uint8_t[];
  using DataT = std::unique_ptr<DataPtrT>;

  Storage() : data_(nullptr), bytes_(0) {}

  explicit Storage(SizeT bytes) : bytes_(bytes) { alloc(); }

  void* data() { return void_data_ptr(); }

  void* data() const { return void_data_ptr(); }

  SizeT bytes() const { return bytes_; }

  template <typename T>
  T& at(SizeT index) {
    CHECK_LE(index, typed_size<T>());
    return typed_data<T>()[index];
  }

  template <typename T>
  const T& at(SizeT index) const {
    CHECK_LE(index, typed_size<T>());
    return typed_data<T>()[index];
  }

  void alloc() { data_ = std::make_unique<DataPtrT>(bytes_); }

  void alloc(SizeT bytes) {
    bytes_ = bytes;
    alloc();
  }

  template <typename T>
  void fill_zero() {
    std::fill(typed_data<T>(), typed_data<T>() + typed_size<T>(), static_cast<T>(0));
  }

  template <typename T>
  void calloc() {
    alloc();
    fill_zero<T>();
  }

protected:
  DataT data_;
  SizeT bytes_;

  void* void_data_ptr() const { return reinterpret_cast<void*>(data_.get()); }

  template <typename T>
  T* typed_data() noexcept {
    return reinterpret_cast<T*>(data());
  }

  template <typename T>
  const T* typed_data() const noexcept {
    return reinterpret_cast<T*>(data());
  }

  template <typename T>
  SizeT typed_size() const noexcept {
    return bytes() / sizeof(T);
  }
};

}  // namespace odnn
