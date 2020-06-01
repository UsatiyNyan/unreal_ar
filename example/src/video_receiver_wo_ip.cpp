//
// Created by kira on 6/1/20.
//

#include "tcp_connection.h"
#include "video_receiver.h"

int main(int argc, char ** argv) {
    tcp::Connection{std::string(argv[1]), 5151};
    video::Receiver{5050}.show_loop();
    return 0;
}
