cmake_minimum_required(VERSION 3.5)
project(ros_autonomy)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -O2")

find_package(rclcpp) # ros client library cpp
find_package(std_msgs) # ros messages library
find_package(ament_cmake)

add_executable(ros_autonomy)

#target_link_libraries(
#    ros_autonomy
#    PUBLIC
#        rclcpp::rclcpp
#        std_msgs
#)

ament_target_dependencies(
    ros_autonomy
    rclcpp
    std_msgs
)


target_sources(
    ros_autonomy 
    PRIVATE 
        main.cpp
)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR})
install(TARGETS ros_autonomy DESTINATION _install)
