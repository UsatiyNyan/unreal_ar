//
// Created by kira on 5/25/20.
//

#include <iostream>
#include "water_state.h"

int main() {
    HeaterCooler heater_cooler;
    std::string cmd;
    std::cout << "cmds: heat and cool" << std::endl;
    std::cout << "current state: " << heater_cooler.state_name() << std::endl;
    while (std::cin >> cmd) {
        if (cmd == "heat") {
            heater_cooler.heat_up();
        } else if (cmd == "cool") {
            heater_cooler.cool_down();
        } else {
            std::cout << "cmds: heat and cool" << std::endl;
        }
        std::cout << "current state: " << heater_cooler.state_name() << std::endl;
    }
    return 0;
}
