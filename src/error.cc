#include "log.h"

#include <sys/types.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <cstdlib>
#include <iostream>

namespace odnn {
namespace {

#ifdef _WIN32
DWORD get_pid() { return GetCurrentProcessId(); }
#else
pid_t get_pid() { return getpid(); }
#endif

void maybe_wait() {
  if (!std::getenv("ODNN_WAIT_ON_CRASH")) return;
  std::cout << "Waiting before crash. You can attach gdb by\n"
            << "$ gdb -p " << get_pid() << std::endl;
  std::string line;
  std::getline(std::cin, line);
}

}  // namespace

FailMessageStream::FailMessageStream(const std::string msg, const char* func, const char* file, int line, bool is_check)
    : msg_(msg), func_(func), file_(file), line_(line), is_check_(is_check) {}

FailMessageStream::~FailMessageStream() {
  if (is_check_) {
    std::cerr << msg_ << " in " << func_ << " at " << file_ << ":" << line_ << ": " << oss_.str() << std::endl;
    maybe_wait();
    std::abort();
  } else {
    std::cerr << oss_.str() << std::endl;
    maybe_wait();
    std::exit(1);
  }
}

}  // namespace odnn
