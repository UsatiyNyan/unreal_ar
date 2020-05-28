//
// Created by kira on 5/26/20.
//

#include "video_receiver.h"

namespace video {
Receiver::Receiver(const std::string &ip, uint16_t port)
    : _server{ip, port}, _stream(_server) {
    _parse_thread = std::thread([this]() {
        while (_server.is_opened()) {
            _stream.find(0xFF);
            if (_stream.next() != 0xD9) { continue; }
            if (_stream.next() != 0xFF) { continue; }
            if (_stream.next() != 0xD8) { continue; }

            {
                std::lock_guard _{_lock};
                _frame = cv::imdecode(_stream.retrieve(), cv::IMREAD_COLOR);
            }
        }
    });
}
Receiver::~Receiver() {
    _server.close();
    _parse_thread.join();
}
void Receiver::show() {
    if (!_frame.empty()) {
        std::lock_guard _{_lock};
        cv::imshow("VideoReceiver", _frame);
    }
}
void Receiver::show_loop() {
    while (_server.is_opened()) {
        show();
    }
}
}  // namespace video
