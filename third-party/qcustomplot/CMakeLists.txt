cmake_minimum_required(VERSION 3.16)
project(qcustomplot C CXX)
enable_testing()

set(CMAKE_AUTOMOC ON)

find_package(Qt6 COMPONENTS Core Widgets PrintSupport REQUIRED)

set(SRC
  "qcustomplot.cpp"
 )

set(HEADERS
  "qcustomplot.h"
)

add_library(qcustomplot ${SRC} ${HEADERS})
target_link_libraries(qcustomplot Qt6::Core Qt6::Widgets Qt6::PrintSupport)
target_include_directories(qcustomplot PUBLIC "../")

export(TARGETS qcustomplot FILE ${CMAKE_SOURCE_DIR}/exported/qcustomplot.cmake)
