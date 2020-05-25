//
// Created by kira on 5/25/20.
//

#include "state_machine.h"

namespace smach {
template <typename StateClass>
StateMachine<StateClass>::StateMachine(StatePtr &&state_ptr) : _state(std::move(state_ptr)) {}
template <typename StateClass>
void StateMachine<StateClass>::set_state(StatePtr &&state_ptr) {
    _state = std::move(state_ptr);
}
}  // namespace smach
