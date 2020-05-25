add_library(state_machine STATIC
        src/water_state_base.cpp
        src/state_machine.cpp
        src/stack_state_machine.cpp
        )
target_include_directories(state_machine PUBLIC include)
