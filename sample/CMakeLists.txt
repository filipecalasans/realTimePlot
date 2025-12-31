cmake_minimum_required(VERSION 3.16)
project(plot_app C CXX)
enable_testing()

set(SRC
  "main.cpp"
  "mainwindow.cpp"
)

set(HEADERS
  "mainwindow.h"
)

set(UI
  "mainwindow.ui"
)

add_executable(plot ${SRC} ${UI} ${HEADERS})
target_link_libraries(plot realtimeplot Qt6::Widgets Qt6::Core)

#export(TARGETS realtimeplot FILE ${CMAKE_SOURCE_DIR}/external/realtimeplot.cmake)
