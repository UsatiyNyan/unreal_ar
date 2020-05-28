//
// Created by kira on 5/28/20.
//

#include "video_transmitter.h"

int main() {
    video::Transmitter transmitter{std::string{"0.0.0.0"}, 8080};
    transmitter.send_loop();
    return 0;
}
