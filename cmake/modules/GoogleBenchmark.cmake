set(GBENCH_VERSION
    "v1.7.1"
    CACHE STRING "Version of GoogleBenchmark")

# Disable the Google Benchmark requirement on Google Test
set(BENCHMARK_ENABLE_TESTING NO)

include(FetchContent)

FetchContent_Declare(
  googlebenchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG ${GBENCH_VERSION})

FetchContent_MakeAvailable(googlebenchmark)
