cmake_minimum_required (VERSION 3.1)
project (hw2_task1)
set(CMAKE_CXX_STANDARD 17) 

if(NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Debug)
endif ()

set(CMAKE_CXX_FLAGS "-Wall -Wextra ")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

include_directories(include/)

add_executable(task_1 src/task_1.cpp)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
install(TARGETS task_1
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        )