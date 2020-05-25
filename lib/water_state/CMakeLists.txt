add_library(water_state STATIC
        src/water_state.cpp
        )
target_include_directories(water_state PUBLIC include)
target_link_libraries(water_state PUBLIC state_machine)
