//
// Created by kira on 3/31/20.
//

#ifndef PROJECT_LIB_TCP_CONNECTION_H_
#define PROJECT_LIB_TCP_CONNECTION_H_

#include <string>
#include <chrono>
#include <netinet/in.h>
#include <vector>

#include "file_descriptor.h"

namespace udp {
constexpr size_t MAX_LEN = 1024;
class Connection {
 protected:
    Connection() = default;
 public:
    Connection(const std::string &ip, uint16_t port);

    Connection(Connection &&other) noexcept;
    Connection &operator=(Connection &&other) noexcept;

    void close();

    size_t write(const void *data, size_t size);
    void write_exact(const void *data, size_t size);
    virtual size_t read(void *data, size_t size);
    void read_exact(void *data, size_t size);

    void set_dst(const std::string &ip, uint16_t port);
    void set_timeout(std::chrono::seconds sec = std::chrono::seconds{},
                     std::chrono::microseconds usec = std::chrono::microseconds{});

    [[nodiscard]] bool is_opened() const;
    [[nodiscard]] std::string const &dst_addr() const;
    [[nodiscard]] std::string const &src_addr() const;
    [[nodiscard]] uint16_t dst_port() const;
    [[nodiscard]] uint16_t src_port() const;
 protected:
    fd::FileDescriptor _fd;
    sockaddr_in _dst_protocol_addr{};
    socklen_t _dst_protocol_addr_len = sizeof(sockaddr_in);
    std::string _dst_addr;
    std::string _src_addr;
    uint16_t _dst_port = 0;
    uint16_t _src_port = 0;
};
}  // namespace udp

#endif //PROJECT_LIB_TCP_CONNECTION_H_
