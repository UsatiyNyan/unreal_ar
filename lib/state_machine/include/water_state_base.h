//
// Created by kira on 5/25/20.
//

#ifndef SMACH_LIB_STATE_MACHINE_SRC_STATE_H_
#define SMACH_LIB_STATE_MACHINE_SRC_STATE_H_

#include <string>
#include "state_machine.h"

namespace smach {
class WaterState {
 public:
    explicit WaterState(StateMachine<WaterState> *machine);
    virtual void heat_up();
    virtual void cool_down();
    [[nodiscard]] virtual std::string name() const = 0;
    virtual ~WaterState();
 protected:
    StateMachine<WaterState> *_machine;
};
}  // namespace smach

#endif //SMACH_LIB_STATE_MACHINE_SRC_STATE_H_
