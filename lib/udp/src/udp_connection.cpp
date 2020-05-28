//
// Created by kira on 3/31/20.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "udp_connection.h"
#include "base_exception.h"


using exception::Exception;

namespace udp {
Connection::Connection(Connection &&other) noexcept {
    _fd = std::move(other._fd);
    _dst_addr = std::move(other._dst_addr);
    _dst_port = other._dst_port;
    _src_addr = std::move(other._src_addr);
    _src_port = other._src_port;
}
Connection &Connection::operator=(Connection &&other) noexcept {
    _fd = std::move(other._fd);
    _dst_addr = std::move(other._dst_addr);
    _dst_port = other._dst_port;
    _src_addr = std::move(other._src_addr);
    _src_port = other._src_port;
    return *this;
}
Connection::Connection(const std::string &ip, uint16_t port) {
    fd::FileDescriptor sock{socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)};
    if (sock.get() == -1) {
        throw Exception("socket creation failed");
    }

    sockaddr_in client_address{};
    socklen_t client_address_size = sizeof(client_address);
    if (getsockname(sock.get(),
            reinterpret_cast<sockaddr *>(&client_address),
            &client_address_size) == -1) {
        throw Exception("client info error");
    }

    set_dst(ip, port);
    _dst_addr = ip;
    _dst_port = port;
    _src_addr = inet_ntoa(client_address.sin_addr);
    _src_port = ntohs(client_address.sin_port);
    _fd = std::move(sock);
}
void Connection::close() {
    _fd.close();
}
void Connection::set_dst(const std::string &ip, uint16_t port) {
    _dst_protocol_addr.sin_family = AF_INET;
    _dst_protocol_addr.sin_addr.s_addr = inet_addr(ip.data());
    _dst_protocol_addr.sin_port = htons(port);
    _dst_protocol_addr_len = sizeof(_dst_protocol_addr);
}
size_t Connection::write(const void *data, size_t size) {
    ssize_t written = sendto(_fd.get(), data, size, 0,
                             reinterpret_cast<sockaddr *>(&_dst_protocol_addr),
                             _dst_protocol_addr_len);
    if (written == -1) {
        _fd.close();
        throw Exception("write error");
    }
    return written;
}
void Connection::write_exact(const void *data, size_t size) {
    size_t written = 0;
    while (size != written) {
        written += write(static_cast<const char *>(data) + written, std::min(size - written, MAX_LEN));
    }
}
size_t Connection::read(void *data, size_t size) {
    ssize_t read_n = ::recv(_fd.get(), data, size, 0);
    if (read_n == -1) {
        _fd.close();
        throw Exception("read error");
    }
    return read_n;
}
void Connection::read_exact(void *data, size_t size) {
    size_t read_n = 0;
    while (size != read_n) {
        read_n += read(static_cast<char *>(data) + read_n, size - read_n);
    }
}
void Connection::set_timeout(std::chrono::seconds sec, std::chrono::microseconds usec) {
    timeval _timeout{.tv_sec = sec.count(), .tv_usec = usec.count()};
    if (setsockopt(_fd.get(),
                   SOL_SOCKET,
                   SO_SNDTIMEO,
                   &_timeout,
                   sizeof(_timeout)) == -1) {
        throw Exception("timeout set failed");
    }
    if (setsockopt(_fd.get(),
                   SOL_SOCKET,
                   SO_RCVTIMEO,
                   &_timeout,
                   sizeof(_timeout)) == -1) {
        throw Exception("timeout set failed");
    }
}
bool Connection::is_opened() const {
    return _fd.get() != -1;
}
std::string const &Connection::dst_addr() const {
    return _dst_addr;
}
std::string const &Connection::src_addr() const {
    return _src_addr;
}
uint16_t Connection::dst_port() const {
    return _dst_port;
}
uint16_t Connection::src_port() const {
    return _src_port;
}
}  // namespace udp
