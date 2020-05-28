//
// Created by kira on 5/25/20.
//

#include "video_transmitter.h"

namespace video {
constexpr int fps = 60;
constexpr int delay = 1000 / fps;
Transmitter::Transmitter(const std::string &ip, uint16_t port)
    : _connection{ip, port} {
    _video_capture.set(cv::CAP_PROP_FPS, 60);
}
void Transmitter::send() {
    _video_capture >> _frame;
    cv::imencode(".jpg", _frame, _frame_jpeg, _compression_params);
    _connection.write_exact(_frame_jpeg.data(), _frame_jpeg.size());
    cv::imshow("origin", _frame);
}
void Transmitter::send_loop() {
    while (cv::waitKey(delay) == -1) {
        send();
    }
}
}  // namespace video
