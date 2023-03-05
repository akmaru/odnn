#pragma once

#include <sstream>
#include <string>

#include "error.h"

namespace odnn {

#define CHECK(cond) \
  while (!(cond)) odnn::FailMessageStream("Check `" #cond "' failed!", __func__, __FILE__, __LINE__)

#define CHECK_CMP(a, b, op)                                                                        \
  while (!((a)op(b)))                                                                              \
  odnn::FailMessageStream("Check `" #a "' " #op " `" #b "' failed!", __func__, __FILE__, __LINE__) \
      << "(" << (a) << " vs " << (b) << ") "

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

}  // namespace odnn
