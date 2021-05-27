cmake_minimum_required(VERSION 3.16) # I checked "cmake --version" before
project(autonomous_unicycle)

set(CMAKE_CXX_STANDARD 17) # It will add the flag "-std=c++17" for all the files

set(CMAKE_CXX_FLAGS "-Wall -O2") # add flags (for instance, the show all warnings flags)

add_library(control)
target_include_directories(control PUBLIC include)
target_sources(control PRIVATE src/control/model_f_euler_dis.cpp src/control/position_controller.cpp)

add_library(planning)
target_include_directories(planning PUBLIC include)
target_sources(planning PRIVATE src/planning/a_star.cpp)

# This needs to be called by the main CMakeLists.txt to setup CTest
enable_testing()
# Add directory with unit-tests
add_subdirectory(test)