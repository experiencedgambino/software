#include "camera/WebCam.hpp"

WebCam::WebCam()
{

} // WebCam

WebCam::~WebCam()
{

} // ~WebCam

bool WebCam::open()
{
    mCapture = new cv::VideoCapture(0);
    if (!mCapture->isOpened())
        return 0;
    return 1;
} // open

bool WebCam::close()
{
    delete mCapture;
} // close

cv::Mat WebCam::getFrame()
{
    cv::Mat frame;
    *mCapture >> frame; // get a new frame from the camera
    return frame;
} // getFrame
