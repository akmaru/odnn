# Google Test
set(GTEST_VERSION
    "v1.13.0"
    CACHE STRING "Version of GoogleTest")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG ${GTEST_VERSION})

# For Windows: Prevent overriding the parent project's compiler/linker settings
if(WIN32)
  set(gtest_force_shared_crt
      ON
      CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()

FetchContent_MakeAvailable(googletest)
include(GoogleTest)
