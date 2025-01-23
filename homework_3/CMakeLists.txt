cmake_minimum_required (VERSION 3.1)
project (hw3)
set(CMAKE_CXX_STANDARD 17) 

if(NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Debug)
endif ()

set(CMAKE_CXX_FLAGS "-Wall -Wextra ")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

include_directories(api/ include/)

add_library(html_writer api/html_writer.cpp)
add_library(image_browser api/image_browser.cpp)

add_executable(create_image_browser src/create_image_browser.cpp)
target_link_libraries(create_image_browser html_writer image_browser)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
install(TARGETS html_writer image_browser create_image_browser
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        )