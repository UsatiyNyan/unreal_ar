//
// Created by kira on 3/31/20.
//

#ifndef PROJECT_LIB_TCP_SERVER_H_
#define PROJECT_LIB_TCP_SERVER_H_

#include <memory>

#include "file_descriptor.h"
#include "udp_connection.h"

namespace udp {
class Server : public Connection {
 public:
    Server(const std::string &ip, uint16_t port);
    size_t read(void *data, size_t size) override;
};
}  // namespace udp

#endif //PROJECT_LIB_TCP_SERVER_H_
