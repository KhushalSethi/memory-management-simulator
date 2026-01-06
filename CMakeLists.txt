cmake_minimum_required(VERSION 3.10)

project(MemoryManagementSimulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(src)
include_directories(src/allocator)
include_directories(src/CLI)
include_directories(src/cache)
include_directories("src/virtual memory")

# Create executable with all source files
add_executable(memsim 
    src/main.cpp
)

# Set output directory
set_target_properties(memsim PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)