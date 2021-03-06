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
        return false;
    return true;
} // open

bool WebCam::close()
{
    delete mCapture;
    return true;
} // close

bool WebCam::getFrame(cv::Mat & frame)
{
    bool return_value = mCapture->read(frame); // get a new frame from the camera
    return return_value;
} // getFrame
