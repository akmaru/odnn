# libtorch
include(FetchContent)

FetchContent_Declare(
  libtorch
  URL https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-1.13.1%2Bcpu.zip
)
FetchContent_GetProperties(libtorch)
if(NOT libtorch_POPULATED)
  FetchContent_Populate(libtorch)
endif()

list(APPEND CMAKE_PREFIX_PATH ${libtorch_SOURCE_DIR})
set(TORCH_LIBRARY_DIRS ${libtorch_SOURCE_DIR}/lib)
find_package(Torch REQUIRED)
