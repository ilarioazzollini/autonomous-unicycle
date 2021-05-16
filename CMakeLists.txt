cmake_minimum_required(VERSION 3.16) # I checked "cmake --version" before
project(autonomous_unicycle)

set(CMAKE_CXX_STANDARD 17) # It will add the flag "-std=c++17" for all the files

set(CMAKE_CXX_FLAGS "-Wall -O2") # add flags (for instance, the show all warnings flags)

add_library(unicycle_control)
target_include_directories(unicycle_control PUBLIC include)
target_sources(unicycle_control PRIVATE src/position_ctrl/model_f_euler_dis.cpp src/position_ctrl/position_controller.cpp)

add_subdirectory(test)