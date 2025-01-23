find_package(PNG REQUIRED)
message(PNG_INCLUDE_DIRS = ${PNG_INCLUDE_DIRS})
message(PNG_LIBS = ${PNG_LIBRARIES})

include_directories(include/ io_strategies/)

# add_library(io_tools io_tools/io_tools.cpp)

add_library(io_strategy io_strategies/png_io_strategy.cpp io_strategies/ppm_io_strategy.cpp)
target_link_libraries(io_strategy ${PNG_LIBRARIES})

add_library(image src/image.cpp)
target_link_libraries(image io_strategy)

add_subdirectory(tests)

