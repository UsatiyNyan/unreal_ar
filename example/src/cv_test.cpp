//
// Created by kira on 5/25/20.
//

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

int main() {
    cv::VideoCapture video_capture(0);
    video_capture.set(cv::CAP_PROP_FPS, 60);

    cv::Mat frame;
    constexpr int fps = 60;
    constexpr int delay = 1000 / fps;

    std::vector<int> compression_params{{cv::IMWRITE_JPEG_QUALITY, 50}};
    std::vector<uchar> frame_jpeg;

    while (cv::waitKey(delay) == -1) {
        video_capture >> frame;
        cv::imshow("origin", frame);
        cv::imencode(".jpg", frame, frame_jpeg, compression_params);
        cv::imshow("jpeg", cv::imdecode(frame_jpeg, cv::IMREAD_COLOR));
//        std::cout << "jpeg_size: " << frame_jpeg.size() << std::endl;
    }
    return 0;
}
