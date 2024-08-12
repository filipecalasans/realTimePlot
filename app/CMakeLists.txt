cmake_minimum_required(VERSION 3.1)
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
target_link_libraries(plot realtimeplot Qt5::Widgets Qt5::Core)

#export(TARGETS realtimeplot FILE ${CMAKE_SOURCE_DIR}/external/realtimeplot.cmake)
