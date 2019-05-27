#ifndef MOTION_DETECTOR_HPP
#define MOTION_DETECTOR_HPP

#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/opencv.hpp>

class MotionDetector
{
public:
    MotionDetector();

    bool detect(cv::Mat frame, cv::Mat reference);

    cv::Mat mFrameOfInterest;
private:

    bool mAreaThreshold;


};

#endif // MOTION_DETECTOR_HPP
