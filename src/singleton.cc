#include "singleton.h"

#include <mutex>

#include "logging.h"

namespace odnn {

namespace {

constexpr int kMaxFinalizersSize = 256;
std::mutex gMutex;
int gNumFinalizersSize = 0;
SingletonFinalizer::FinalizerFunc gFinalizers[kMaxFinalizersSize];

}  // namespace

void SingletonFinalizer::addFinalizer(FinalizerFunc func) {
  std::lock_guard<std::mutex> lock(gMutex);
  CHECK_LT(gNumFinalizersSize, kMaxFinalizersSize);
  gFinalizers[gNumFinalizersSize++] = func;
}

void SingletonFinalizer::finalize() {
  std::lock_guard<std::mutex> lock(gMutex);
  for (int i = gNumFinalizersSize - 1; i >= 0; --i) {
    (*gFinalizers[i])();
  }
  gNumFinalizersSize = 0;
}

}  // namespace odnn
