//
// Created by kira on 5/26/20.
//

#include "video_receiver.h"
#include "video_settings.h"
#include "base_exception.h"

using exception::Exception;

namespace video {
Receiver::Receiver(uint16_t port) {
    std::string api_cmd(
        "udpsrc port=" + std::to_string(port) + " "
        "! application/x-rtp,media=video,payload=26,clock-rate=90000,encoding-name=JPEG,"
        "framerate=" + std::to_string(Settings::FPS) + "/1 "
        "! rtpjpegdepay "
        "! jpegdec "
        "! videoconvert "
        "! appsink"
        );
    _capture = cv::VideoCapture(api_cmd, cv::CAP_GSTREAMER);
    if (!_capture.isOpened()) {
        throw Exception("VideoCapture not opened");
    }
}
void Receiver::show() {
    _capture.read(_frame);
    imshow("received", _frame);
}
void Receiver::show_loop() {
    while (cv::waitKey(Settings::DELAY) == -1) {
        show();
    }
}
}  // namespace video
