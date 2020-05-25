//
// Created by kira on 5/25/20.
//

#ifndef SMACH_LIB_STATE_MACHINE_INCLUDE_STACK_STATE_MACHINE_H_
#define SMACH_LIB_STATE_MACHINE_INCLUDE_STACK_STATE_MACHINE_H_

#include <vector>
#include <memory>

namespace smach {
template <class StateClass>
class StackStateMachine {
    using StatePtr = std::unique_ptr<StateClass>;
 public:
    explicit StackStateMachine(StatePtr &&state_ptr) {
        _states.push_back(std::move(state_ptr));
    }
    void add_state(StatePtr && state_ptr) {
        _states.push_back(std::move(state_ptr));
    }
    void pop_state() {
        _states.pop_back();
    }
    StatePtr &current_state() const {
        return _states.back();
    }
 private:
    std::vector<StatePtr> _states;
};
}  // namespace smach

#endif //SMACH_LIB_STATE_MACHINE_INCLUDE_STACK_STATE_MACHINE_H_
