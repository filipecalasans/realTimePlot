cmake_minimum_required(VERSION 3.1)
project(plot_app C CXX)
enable_testing()

set(SRC
  "main.cpp"
  "mainwindow.cpp"
  "ui/signalsourceselectdialog.cpp"
)

set(HEADERS
  "mainwindow.h.h"
  "ui/signalsourceselectdialog.h"
  )

set(UI
  "mainwindow.ui"
  "ui/signalsourceselectdialog.ui"
)

add_executable(plot ${SRC} ${UI})
target_link_libraries(plot realtimeplot Qt5::Widgets Qt5::Core)

#export(TARGETS realtimeplot FILE ${CMAKE_SOURCE_DIR}/external/realtimeplot.cmake)
