add_library(process STATIC
        src/process.cpp
        )
target_link_libraries(process file_descriptor base_exception)
target_include_directories(process PUBLIC include)
