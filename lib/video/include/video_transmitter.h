//
// Created by kira on 5/25/20.
//

#ifndef SMACH_LIB_VIDEO_TRANSMITTER_INCLUDE_VIDEO_TRANSMITTER_H_
#define SMACH_LIB_VIDEO_TRANSMITTER_INCLUDE_VIDEO_TRANSMITTER_H_

#include "udp_connection.h"

#include <opencv2/opencv.hpp>

namespace video {
class Transmitter {
 public:
    Transmitter(const std::string &ip, uint16_t port);
    void send();
    void send_loop();
 private:
    udp::Connection _connection;
    cv::Mat _frame;
    std::vector<uchar> _frame_jpeg;
    cv::VideoCapture _video_capture{2};
    std::vector<int> _compression_params{{cv::IMWRITE_JPEG_QUALITY, 80}};
};
}  // namespace video

#endif //SMACH_LIB_VIDEO_TRANSMITTER_INCLUDE_VIDEO_TRANSMITTER_H_
