add_library(tcp STATIC
        src/tcp_server.cpp
        src/tcp_connection.cpp)
target_link_libraries(tcp file_descriptor base_exception)
target_include_directories(tcp PUBLIC include)
