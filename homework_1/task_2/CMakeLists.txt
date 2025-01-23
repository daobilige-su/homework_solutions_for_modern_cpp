cmake_minimum_required (VERSION 3.1)
project (hw1_task2)
set(CMAKE_CXX_STANDARD 17) 

if(NOT CMAKE_BUILD_TYPE )
    set( CMAKE_BUILD_TYPE Debug)
endif ()

set(CMAKE_CXX_FLAGS "-Wall -Wextra ")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

include_directories(include/)

add_library(ipb_arithmetic_lib src/subtract.cpp src/sum.cpp)

add_executable(test_ipb_arithmetic src/main.cpp)

target_link_libraries(test_ipb_arithmetic ipb_arithmetic_lib)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install)

install(TARGETS ipb_arithmetic_lib
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        )
install(FILES ./include/ipb_arithmetic.hpp 
        DESTINATION include)
install(FILES ./include/ipb_arithmetic/subtract.hpp 
        ./include/ipb_arithmetic/sum.hpp
        DESTINATION include/ipb_arithmetic)
