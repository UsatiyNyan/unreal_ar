add_library(video STATIC
        src/video_transmitter.cpp
        src/video_receiver.cpp
        )
target_include_directories(video PUBLIC include)
find_package(OpenCV REQUIRED)
target_link_libraries(video PUBLIC ${OpenCV_LIBS} base_exception)
