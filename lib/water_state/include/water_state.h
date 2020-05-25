//
// Created by kira on 5/25/20.
//

#ifndef SMACH_EXAMPLE_SRC_WATER_STATE_H_
#define SMACH_EXAMPLE_SRC_WATER_STATE_H_

#include "water_state_base.h"
#include <string>

class Water: public smach::WaterState {
 public:
    explicit Water(smach::StateMachine<WaterState> *machine) : WaterState(machine) {};
    void heat_up() override;
    void cool_down() override;
    [[nodiscard]] std::string name() const override;
};

class Ice: public smach::WaterState {
 public:
    explicit Ice(smach::StateMachine<WaterState> *machine) : WaterState(machine) {};
    void heat_up() override;
    [[nodiscard]] std::string name() const override;
};

class Steam: public smach::WaterState {
 public:
    explicit Steam(smach::StateMachine<WaterState> *machine) : WaterState(machine) {};
    void cool_down() override;
    [[nodiscard]] std::string name() const override;
};

class HeaterCooler : public smach::StateMachine<smach::WaterState> {
 public:
    HeaterCooler() : StateMachine(std::move(std::make_unique<Water>(this))) {}
    void heat_up();
    void cool_down();
    [[nodiscard]] std::string state_name() const;
};

#endif //SMACH_EXAMPLE_SRC_WATER_STATE_H_
