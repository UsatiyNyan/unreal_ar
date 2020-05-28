//
// Created by kira on 5/26/20.
//

#ifndef SMACH_LIB_VIDEO_TRANSMITTER_INCLUDE_VIDEO_RECIEVER_H_
#define SMACH_LIB_VIDEO_TRANSMITTER_INCLUDE_VIDEO_RECIEVER_H_

#include "udp_data_stream.h"
#include "udp_server.h"

#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>

namespace video {
class Receiver {
 public:
    Receiver(const std::string &ip, uint16_t port);
    ~Receiver();
    void show();
    void show_loop();
 private:
    udp::Server _server;
    udp::DataStream<uchar> _stream;
    cv::Mat _frame;
    std::mutex _lock;
    std::thread _parse_thread;
};
}  // namespace video

#endif //SMACH_LIB_VIDEO_TRANSMITTER_INCLUDE_VIDEO_RECIEVER_H_
