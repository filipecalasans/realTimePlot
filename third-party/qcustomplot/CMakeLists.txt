cmake_minimum_required(VERSION 3.1)
project(qcustomplot C CXX)
enable_testing()

find_package(Qt5PrintSupport REQUIRED)

set(SRC
  "qcustomplot.cpp"
 )

set(HEADERS
  "qcustomplot.h"
)

add_library(qcustomplot ${SRC})
target_link_libraries(qcustomplot Qt5::Widgets Qt5::PrintSupport)
target_include_directories(qcustomplot PUBLIC "../")

export(TARGETS qcustomplot FILE ${CMAKE_SOURCE_DIR}/exported/qcustomplot.cmake)
