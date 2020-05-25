//
// Created by kira on 5/25/20.
//

#ifndef SMACH_LIB_STATE_MACHINE_SRC_STATE_MACHINE_H_
#define SMACH_LIB_STATE_MACHINE_SRC_STATE_MACHINE_H_

#include <memory>

namespace smach {
template <typename StateClass>
class StateMachine {
    using StatePtr = std::unique_ptr<StateClass>;
 public:
    explicit StateMachine(StatePtr &&state_ptr);
    void set_state(StatePtr &&state_ptr);
 protected:
    StatePtr _state;
};
}  // namespace smach

#endif //SMACH_LIB_STATE_MACHINE_SRC_STATE_MACHINE_H_
