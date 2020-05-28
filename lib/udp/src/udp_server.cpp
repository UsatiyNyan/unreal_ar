//
// Created by kira on 3/31/20.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "udp_server.h"


using exception::Exception;

namespace udp {
Server::Server(const std::string &ip, uint16_t port) : Connection() {
    auto listener = fd::FileDescriptor{socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)};
    if (listener.get() == -1) {
        throw Exception("socket creation failed");
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip.c_str());
    if (bind(listener.get(),
             reinterpret_cast<sockaddr *>(&addr),
             sizeof(addr)) == -1) {
        throw Exception("bind failed");
    }

    _src_addr = ip;
    _src_port = port;
    _fd = std::move(listener);
}
size_t Server::read(void *data, size_t size) {
    if (_dst_protocol_addr.sin_port != 0) {
        return Connection::read(data, size);
    }
    ssize_t read_n = ::recvfrom(_fd.get(), data, size, 0,
                                reinterpret_cast<sockaddr *>(&_dst_protocol_addr), &_dst_protocol_addr_len);
    if (read_n == -1) {
        _fd.close();
        throw Exception("read error");
    }
    return read_n;
}
}  // namespace udp
