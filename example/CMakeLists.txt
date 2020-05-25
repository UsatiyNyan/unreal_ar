add_executable(water_state_usage src/water_state_usage.cpp)
target_link_libraries(water_state_usage water_state)


find_package(OpenCV REQUIRED)
message(${OpenCV_VERSION})
add_executable(cv_test src/cv_test.cpp)
target_link_libraries(cv_test )
