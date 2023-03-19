include(${PROJECT_SOURCE_DIR}/cmake/modules/GoogleLogging.cmake)

file(GLOB_RECURSE SRC_HDRS *.h)
file(GLOB_RECURSE SRC_SRCS *.cc)

add_library(odnn ${SRC_SRCS} ${SRC_HDRS})

target_include_directories(odnn PUBLIC glog::glog ${ODNN_INCLUDE_DIRS})
target_link_libraries(odnn PUBLIC glog::glog)
