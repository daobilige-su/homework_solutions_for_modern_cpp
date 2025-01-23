cmake_minimum_required (VERSION 3.1)
project (hw8)
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

include_directories(include/ task_2/include/ task_2/io_strategies ${OpenCV_INCLUDE_DIRS} )

add_executable(stack_limit task_1/src/stack_limit.cpp)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
install(TARGETS stack_limit DESTINATION task_1/bin)

add_subdirectory(task_2)

# add_subdirectory(task_2/tests)
