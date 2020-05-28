//
// Created by kira on 5/28/20.
//

#include "video_receiver.h"

int main() {
    video::Receiver receiver{std::string{"0.0.0.0"}, 8080};
    receiver.show_loop();
    return 0;
}
