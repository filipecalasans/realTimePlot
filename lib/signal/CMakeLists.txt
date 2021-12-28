cmake_minimum_required(VERSION 3.1)
project(realtimeplot C CXX)
enable_testing()

set(SRC
  "pointstream.cpp"
)

set(HEADERS
  "pointstream.h"
)

add_library(signal ${SRC} ${UI})
target_link_libraries(signal qcustomplot cpp_ringbuffer Qt5::Widgets)
target_include_directories(signal PUBLIC "../")
