cmake_minimum_required(VERSION 3.7)

project(SDL2Test CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SDL2 package
find_package(SDL2 REQUIRED)

# Add the executable
add_executable(chip8
    src/main.cpp
    src/CHIP.cpp
    src/audio.cpp
    src/display.cpp
    src/CHIP.h
    src/display.h
    src/audio.h
)

# Include directories
target_include_directories(chip8 PRIVATE
    ${SDL2_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/src
)

# Link SDL2 and pthread libraries
target_link_libraries(chip8
    ${SDL2_LIBRARIES}
    pthread
)

# Optionally, you can set additional compiler flags if needed
target_compile_options(chip8 PRIVATE
    -Wall
)

