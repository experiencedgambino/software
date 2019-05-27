#ifndef FRAME_PROCESSOR_HPP
#define FRAME_PROCESSOR_HPP

#include "opencv2/imgproc/imgproc.hpp"

class BackgroundSubtractor
{
public:
    // Default constructor
    BackgroundSubtractor();

    // Reset the background frame
    void resetBackground(cv::Mat & frame);

    // Add a cv2::Mat to the background at a certain percentage
    void addFrame(cv::Mat frame, float percentNew);

    // Returns the current background frame of the thing
    cv::Mat getBackground();

private:
    cv::Mat mBackground;
    cv::Mat mDiff;

}; // FrameProcessor

#endif // FRAME_PROCESSOR_HPP
