//
// Created by kira on 5/28/20.
//

#include "video_transmitter.h"

int main() {
    video::Transmitter{"0.0.0.0", 5050, 2}.send_loop();
    return 0;
}

