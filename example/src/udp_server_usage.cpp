//
// Created by kira on 5/26/20.
//

#include "udp_server.h"
#include <iostream>

int main() {
    udp::Server server{"0.0.0.0", 7331};
    std::string to_read(0b1000, 0);
    server.read_exact(to_read.data(), to_read.size());
    std::cout << to_read << std::endl;

    std::string to_send{"MUDA"};
    std::cout << server.write(to_send.data(), to_send.size()) << std::endl;

    return 0;
}
