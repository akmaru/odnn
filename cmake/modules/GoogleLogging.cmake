# Google Test
set(GLOG_VERSION
    "v0.6.0"
    CACHE STRING "Version of Google Logging")

set(WITH_GFLAGS
    OFF
    CACHE INTERNAL "Use gflags in glog")
set(WITH_GTEST
    OFF
    CACHE INTERNAL "Use Google Test in glog")
set(WITH_PKGCONFIG
    OFF
    CACHE INTERNAL "Enable pkg-config support in glog")
set(WITH_UNWIND
    OFF
    CACHE INTERNAL "Enable libunwind support in glog")
set(BUILD_TESTING
    OFF
    CACHE INTERNAL "Enable build test in glog")

include(FetchContent)
FetchContent_Declare(
  glog
  GIT_REPOSITORY https://github.com/google/glog.git
  GIT_TAG ${GLOG_VERSION})

FetchContent_MakeAvailable(glog)
