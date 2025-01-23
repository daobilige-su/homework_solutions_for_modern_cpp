cmake_minimum_required (VERSION 3.1)
project (hw6)
set(CMAKE_CXX_STANDARD 17) 

if(NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Debug)
endif ()

set(CMAKE_CXX_FLAGS "-Wall -Wextra ")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fno-limit-debug-info")

set(OpenCV_DIR /usr/local/lib/cmake/opencv4)
find_package(OpenCV REQUIRED)
message(OpenCV_VERSION = ${OpenCV_VERSION})
message(OpenCV_DIR = ${OpenCV_DIR})

include_directories(include/ io_tools/ ${OpenCV_INCLUDE_DIRS} )

add_library(io_tools io_tools/io_tools.cpp)

add_library(image src/image.cpp)
target_link_libraries(image io_tools)

# add_library(convert_dataset src/convert_dataset.cpp)
# target_link_libraries(convert_dataset ${OpenCV_LIBS} mat_serialization)

# add_executable(convert_freiburg_dataset src/convert_freiburg_dataset.cpp)
# target_link_libraries(convert_freiburg_dataset mat_serialization convert_dataset)

# add_subdirectory(io_tools)

add_subdirectory(tests)

add_executable(test src/test_specials.cpp)
target_link_libraries(test image)
