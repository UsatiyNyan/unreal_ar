//
// Created by kira on 5/25/20.
//

#include "water_state.h"
void Water::heat_up() {
    _machine->set_state(std::move(std::make_unique<Steam>(_machine)));
}
void Water::cool_down() {
    _machine->set_state(std::move(std::make_unique<Ice>(_machine)));
}
std::string Water::name() const {
    return "Water";
}
void Ice::heat_up() {
    _machine->set_state(std::move(std::make_unique<Water>(_machine)));
}
std::string Ice::name() const {
    return "Ice";
}
void Steam::cool_down() {
    _machine->set_state(std::move(std::make_unique<Water>(_machine)));
}
std::string Steam::name() const {
    return "Steam";
}
void HeaterCooler::heat_up() {
    _state->heat_up();
}
void HeaterCooler::cool_down() {
    _state->cool_down();
}
std::string HeaterCooler::state_name() const {
    return _state->name();
}
