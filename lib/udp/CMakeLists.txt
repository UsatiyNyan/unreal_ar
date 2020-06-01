add_library(udp STATIC
        src/udp_server.cpp
        src/udp_connection.cpp)
target_link_libraries(udp file_descriptor base_exception)
target_include_directories(udp PUBLIC include)
