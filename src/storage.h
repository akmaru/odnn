#pragma once

#include <algorithm>
#include <cstdint>
#include <memory>

namespace odnn {

class Storage {
public:
  using SizeT = std::int64_t;
  using DataPtrT = std::uint8_t[];
  using DataT = std::unique_ptr<DataPtrT>;

  Storage() : data_(nullptr), bytes_(0) {}

  explicit Storage(SizeT bytes) : bytes_(bytes) { alloc(); }

  void* data() { return void_data_ptr(); }

  void* data() const { return void_data_ptr(); }

  SizeT bytes() const { return bytes_; }

  template <typename T>
  void fill_zero() {
    auto* typed_ptr = reinterpret_cast<T*>(data());
    const auto typed_size = bytes() / sizeof(T);
    std::fill(typed_ptr, typed_ptr + typed_size, static_cast<T>(0));
  }

protected:
  DataT data_;
  SizeT bytes_;

  void alloc() { data_ = std::make_unique<DataPtrT>(bytes_); }

  void* void_data_ptr() const { return reinterpret_cast<void*>(data_.get()); }
};

}  // namespace odnn
