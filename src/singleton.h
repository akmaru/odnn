#pragma once

#include <glog/logging.h>

#include <mutex>

namespace odnn {

class SingletonFinalizer {
public:
  using FinalizerFunc = void (*)();
  static void addFinalizer(FinalizerFunc func);
  static void finalize();
};

template <typename T>
class Singleton final {
public:
  static T& get() {
    std::call_once(init_flag_, create);
    CHECK(instance_);
    return *instance_;
  }

private:
  static void create() {
    instance_ = new T;
    SingletonFinalizer::addFinalizer(&Singleton<T>::destroy);
  }

  static void destroy() {
    delete instance_;
    instance_ = nullptr;
  }

  static std::once_flag init_flag_;
  static T* instance_;
};

template <typename T>
std::once_flag Singleton<T>::init_flag_;

template <typename T>
T* Singleton<T>::instance_ = nullptr;

}  // namespace odnn
