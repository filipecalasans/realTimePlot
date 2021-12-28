cmake_minimum_required(VERSION 3.1)
project(realtimeplot C CXX)
enable_testing()

set(SRC
  "plotarea.cpp"
)

set(HEADERS
  "plotarea.h"
)

set(UI
  "plotarea.ui"
)

add_library(realtimeplot ${SRC} ${UI})
target_link_libraries(realtimeplot signal qcustomplot cpp_ringbuffer Qt5::Widgets)
target_include_directories(realtimeplot PUBLIC "../")

export(TARGETS realtimeplot FILE ${CMAKE_SOURCE_DIR}/exported/realtimeplot.cmake)
