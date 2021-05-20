# Search gtest library
find_package(GTest)

add_executable(test_model)
target_link_libraries(test_model PUBLIC unicycle_control GTest::GTest)
target_sources(test_model PRIVATE test_model.cpp)
add_test(NAME test_model COMMAND test_model)

add_executable(test_position_controller)
target_link_libraries(test_position_controller PUBLIC unicycle_control GTest::GTest)
target_sources(test_position_controller PRIVATE test_position_controller.cpp)
add_test(NAME test_position_controller COMMAND test_position_controller)
