#pragma once

#include <sstream>
#include <string>

namespace odnn {

class FailMessageStream {
public:
  FailMessageStream(const std::string msg, const char* func, const char* file, int line, bool is_check = true);

  ~FailMessageStream();

  template <class T>
  FailMessageStream& operator<<(const T& v) {
    oss_ << v;
    return *this;
  }

private:
  std::ostringstream oss_;
  const std::string msg_;
  const char* func_;
  const char* file_;
  const int line_;
  const bool is_check_;
};

#define QFAIL() odnn::FailMessageStream("", __func__, __FILE__, __LINE__, false)

#define UNIMPLENTED() odnn::FailMessageStream("Not implemented", __func__, __FILE__, __LINE__)

#define UNREACHABLE() odnn::FailMessageStream("Entered unreachable code", __func__, __FILE__, __LINE__)

}  // namespace odnn
