#include "logging.h"

#include <sys/types.h>

#include <sstream>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <ctime>
#include <iomanip>
#include <iostream>

namespace odnn {
namespace detail {

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

std::string log_prefix_format(
    std::time_t timestamp, const std::string& level, const std::string& file, int line
) {
  std::ostringstream oss;
  oss << "[" << std::put_time(std::localtime(&timestamp), "%F %T");
  oss << std::setw(6) << level;
  oss << " " << file << ":" << line << "]";

  return oss.str();
}

}  // namespace

FatalMessage::FatalMessage(
    const std::string& msg, const char* func, const char* file, int line, bool is_check
)
    : msg_(msg), func_(func), file_(file), line_(line), is_check_(is_check) {}

FatalMessage::~FatalMessage() {
  if (is_check_) {
    std::cerr << msg_ << " in " << func_ << " at " << file_ << ":" << line_ << ": " << oss_.str()
              << std::endl;
    maybe_wait();
    std::abort();
  } else {
    std::cerr << oss_.str() << std::endl;
    maybe_wait();
    std::exit(1);
  }
}

const char* LogMessage::level_strings_[] = {
    "TRACE",  // ODNN_LOG_LEVEL_TRACD
    "DEBUG",  // ODNN_LOG_LEVEL_DEBUG
    "INFO",   // ODNN_LOG_LEVEL_INFO
    "WARN",   // ODNN_LOG_LEVEL_WARNING
    "ERROR",  // ODNN_LOG_LEVEL_ERROR
};

LogMessage::LogMessage(const char* file, int line, int level)
    : file_(file), line_(line), level_(level) {
  timestamp_ = std::time(nullptr);
  oss_ << "[" << std::put_time(std::localtime(&timestamp_), "%H:%M:%S") << "] " << file << ":"
       << line << level_strings_[level];
}

LogMessage::~LogMessage() { std::cerr << oss_.str() << std::endl; }

}  // namespace detail
}  // namespace odnn
