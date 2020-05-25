//
// Created by kira on 5/25/20.
//

#include "water_state_base.h"
#include <iostream>

namespace smach {

WaterState::WaterState(StateMachine<WaterState> *machine) : _machine(machine) {
    std::cerr << "c-ted" << std::endl;
}
void WaterState::heat_up() {}
void WaterState::cool_down() {}
WaterState::~WaterState() {
    std::cerr << "d-ted" << std::endl;
}
}  // namespace smach
