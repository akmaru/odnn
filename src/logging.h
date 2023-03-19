#pragma once

#include <ctime>
#include <sstream>
#include <string>

namespace odnn {
namespace detail {

class LogMessage {
public:
  LogMessage(const char* file, int line, int level);

  ~LogMessage();

  template <class T>
  LogMessage& operator<<(const T& v) {
    oss_ << v;
    return *this;
  }

private:
  std::ostringstream oss_;
  const char* file_;
  const int line_;
  int level_;
  std::time_t timestamp_;
  static const char* level_strings_[];
};

class FatalMessage {
public:
  FatalMessage(
      const std::string& msg, const char* func, const char* file, int line, bool is_check = true
  );

  ~FatalMessage();

  template <class T>
  FatalMessage& operator<<(const T& v) {
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

}  // namespace detail

// LOG macros
#define ODNN_LOG_LEVEL_TRACE 0
#define ODNN_LOG_LEVEL_DEBUG 1
#define ODNN_LOG_LEVEL_INFO 2
#define ODNN_LOG_LEVEL_WARNING 3
#define ODNN_LOG_LEVEL_ERROR 4
#define ODNN_LOG_LEVEL_FATAL 5

#define LOG(level) LOG_##level
#define LOG_DEBUG ::odnn::detail::LogMessage(__FILE__, __LINE__, ODNN_LOG_LEVEL_DEBUG)
#define LOG_INFO ::odnn::detail::LogMessage(__FILE__, __LINE__, ODNN_LOG_LEVEL_INFO)
#define LOG_WARNING ::odnn::detail::LogMessage(__FILE__, __LINE__, ODNN_LOG_LEVEL_WARNING)
#define LOG_ERROR ::odnn::detail::LogMessage(__FILE__, __LINE__, ODNN_LOG_LEVEL_ERROR)
#define LOG_FATAL ::odnn::detail::FatalMessage("", __func__, __FILE__, __LINE__)

#ifdef NDEBUG
#define DLOG(level)
#else
#define DLOG(level) LOG(level)
#endif

// CHECK macros
#define CHECK(cond) \
  while (!(cond))   \
  ::odnn::detail::FatalMessage("Check `" #cond "' failed!", __func__, __FILE__, __LINE__)

#define CHECK_CMP(a, b, op)                                                   \
  while (!((a)op(b)))                                                         \
  ::odnn::detail::FatalMessage(                                               \
      "Check `" #a "' " #op " `" #b "' failed!", __func__, __FILE__, __LINE__ \
  ) << "("                                                                    \
    << (a) << " vs " << (b) << ") "

#define CHECK_EQ(a, b) CHECK_CMP(a, b, ==)
#define CHECK_NE(a, b) CHECK_CMP(a, b, !=)
#define CHECK_LT(a, b) CHECK_CMP(a, b, <)
#define CHECK_LE(a, b) CHECK_CMP(a, b, <=)
#define CHECK_GT(a, b) CHECK_CMP(a, b, >)
#define CHECK_GE(a, b) CHECK_CMP(a, b, >=)

#ifdef NDEBUG
#define DCHECK(cond)
#define DCHECK_EQ(a, b)
#define DCHECK_NE(a, b)
#define DCHECK_LT(a, b)
#define DCHECK_LE(a, b)
#define DCHECK_GT(a, b)
#define DCHECK_GE(a, b)
#else
#define DCHECK(cond) CHECK(cond)
#define DCHECK_EQ(a, b) CHECK_EQ(a, b)
#define DCHECK_NE(a, b) CHECK_NE(a, b)
#define DCHECK_LT(a, b) CHECK_LT(a, b)
#define DCHECK_LE(a, b) CHECK_LE(a, b)
#define DCHECK_GT(a, b) CHECK_GT(a, b)
#define DCHECK_GE(a, b) CHECK_GE(a, b)
#endif

#define WARN_ONCE(msg)                                                    \
  do {                                                                    \
    static bool logged_##__LINE__ = false;                                \
    if (!logged_##__LINE__) std::cerr << "WARNING: " << msg << std::endl; \
    logged_##__LINE__ = true;                                             \
  } while (0)

#define QFAIL() ::odnn::detail::FatalMessage("", __func__, __FILE__, __LINE__, false)
#define UNIMPLENTED() ::odnn::detail::FatalMessage("Not implemented", __func__, __FILE__, __LINE__)
#define UNREACHABLE() \
  ::odnn::detail::FatalMessage("Entered unreachable code", __func__, __FILE__, __LINE__)

}  // namespace odnn
