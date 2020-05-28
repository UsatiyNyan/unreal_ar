//
// Created by kira on 5/26/20.
//

#include "udp_connection.h"
#include <iostream>

int main() {
    udp::Connection connection{"0.0.0.0", 7331};

    std::string to_send(0b100, 'x');
    connection.write_exact(to_send.data(), to_send.size());
    connection.write_exact(to_send.data(), to_send.size());

    std::string to_read(128, 0);
    std::cout << connection.read(to_read.data(), to_read.size()) << std::endl;
    std::cout << to_read << std::endl;

    return 0;
}