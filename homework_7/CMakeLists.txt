cmake_minimum_required (VERSION 3.1)
project (hw7)
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

include_directories(include/ ${OpenCV_INCLUDE_DIRS} )

add_library(kmeans src/kmeans.cpp)
target_link_libraries(kmeans ${OpenCV_LIBS})

add_library(serialization src/serialize.cpp src/convert_dataset.cpp)
target_link_libraries(serialization ${OpenCV_LIBS})

add_library(bow_dictionary src/BowDictionary.cpp)
target_link_libraries(bow_dictionary kmeans ${OpenCV_LIBS})

add_subdirectory(tests)
