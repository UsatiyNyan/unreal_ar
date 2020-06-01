add_executable(water_state_usage src/water_state_usage.cpp)
target_link_libraries(water_state_usage water_state)

add_executable(cv_test src/cv_test.cpp)
target_link_libraries(cv_test video)

add_executable(udp_client_usage src/udp_client_usage.cpp)
target_link_libraries(udp_client_usage udp)

add_executable(udp_server_usage src/udp_server_usage.cpp)
target_link_libraries(udp_server_usage udp)

add_executable(video_transmitter_usage src/video_transmitter_usage.cpp)
target_link_libraries(video_transmitter_usage video)

add_executable(video_receiver_usage src/video_receiver_usage.cpp)
target_link_libraries(video_receiver_usage video)

add_executable(video_streamer_wo_ip src/video_streamer_wo_ip.cpp)
target_link_libraries(video_streamer_wo_ip video tcp)

add_executable(video_receiver_wo_ip src/video_receiver_wo_ip.cpp)
target_link_libraries(video_receiver_wo_ip video tcp)
