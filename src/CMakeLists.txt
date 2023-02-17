file(GLOB SRC_HDRS *.h)
file(GLOB SRC_SRCS *.cc)

add_library(
    odnn
    ${SRC_SRCS}
    ${SRC_HDRS}
)
