cmake_minimum_required(VERSION 3.16)
project(real_time_plot VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

enable_testing()

find_package(Qt6 COMPONENTS Core REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_subdirectory(third-party)
add_subdirectory(lib)
add_subdirectory(sample)
