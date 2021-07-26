cmake_minimum_required(VERSION 3.16) # I checked "cmake --version" before
project(autonomy)

set(CMAKE_CXX_STANDARD 17) # It will add the flag "-std=c++17" for all the files

set(CMAKE_CXX_FLAGS "-Wall -O2") # add flags (for instance, the show all warnings flags)

add_library(autonomy)
target_include_directories(autonomy PUBLIC include)
target_sources(
    autonomy 
    PRIVATE 
        src/control/model_f_euler_dis.cpp
        src/control/position_controller.cpp
        src/planning/a_star.cpp
)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
install(TARGETS autonomy DESTINATION _install)

# This needs to be called by the main CMakeLists.txt to setup CTest
enable_testing()
# Add directory with unit-tests
add_subdirectory(test)
