//
// Created by kira on 6/1/20.
//

#include "tcp_server.h"
#include "video_transmitter.h"

int main() {;
    const std::string& ip = tcp::Server{"0.0.0.0", 5151}.accept().dst_addr();
//    std::string ip = "0.0.0.0";
    video::Transmitter{ip, 5050, 2}.send_loop();
    return 0;
}
