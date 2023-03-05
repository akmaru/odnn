include(${PROJECT_SOURCE_DIR}/cmake/modules/GoogleTest.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/modules/libTorch.cmake)

file(GLOB TEST_SRCS *.cc)

foreach(test_path ${TEST_SRCS})
  get_filename_component(test_file ${test_path} NAME)
  string(REPLACE ".cc" "" test_name ${test_file})
  add_executable(${test_name} ${test_file})
  target_include_directories(
    ${test_name} PRIVATE ${ODNN_INCLUDE_DIRS} ${ODNN_SRC_DIR}
                         ${TORCH_INCLUDE_DIRS})
  target_compile_options(${test_name} PRIVATE ${ODNN_CXX_FLAGS})
  target_link_libraries(${test_name} PRIVATE odnn GTest::gtest_main
                                             ${TORCH_LIBRARIES})
  gtest_discover_tests(${test_name})
endforeach()

add_subdirectory(nn)
