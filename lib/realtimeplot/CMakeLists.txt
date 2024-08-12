cmake_minimum_required(VERSION 3.1)
project(realtimeplot C CXX)
enable_testing()

set(SRC
  "pointstream.cpp"
  "plotarea.cpp"
)

set(HEADERS
  "pointstream.h"
  "plotarea.h"
)

set(UI
  "plotarea.ui"
)

add_library(realtimeplot ${HEADERS} ${SRC} ${UI})
target_link_libraries(realtimeplot qcustomplot cpp_ringbuffer Qt5::Widgets)
target_include_directories(realtimeplot PUBLIC "../")

export(TARGETS realtimeplot FILE ${CMAKE_SOURCE_DIR}/exported/realtimeplot.cmake)
