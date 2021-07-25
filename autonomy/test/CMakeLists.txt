# Search gtest library
find_package(GTest)

add_executable(test_model)
target_link_libraries(test_model PUBLIC autonomy GTest::GTest)
target_sources(test_model PRIVATE test_model.cpp)
add_test(NAME test_model COMMAND test_model)

add_executable(test_matrix)
target_link_libraries(test_matrix PUBLIC autonomy GTest::GTest)
target_sources(test_matrix PRIVATE test_matrix.cpp)
add_test(NAME test_matrix COMMAND test_matrix)

add_executable(test_position_controller)
target_link_libraries(test_position_controller PUBLIC autonomy GTest::GTest)
target_sources(test_position_controller PRIVATE test_position_controller.cpp)
add_test(NAME test_position_controller COMMAND test_position_controller)

add_executable(test_planner)
target_link_libraries(test_planner PUBLIC autonomy GTest::GTest)
target_sources(test_planner PRIVATE test_planner.cpp)
add_test(NAME test_planner COMMAND test_planner)
