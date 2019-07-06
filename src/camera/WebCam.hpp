#ifndef CAMERA_WEBCAM_HPP
#define CAMERA_WEBCAM_HPP

#include "opencv2/videoio.hpp"
#include "camera/Camera.hpp"

class WebCam : public Camera
{
public:
    // Constructor
    WebCam();

    // Destructor
    ~WebCam();

    // Camera:getFrame
    bool getFrame(cv::Mat & frame);

    // Camera:open
    bool open();

    // Camera:close
    bool close();

    // isOpen
    bool isOpen();
private:
    // VideoCapture object
    cv::VideoCapture * mCapture;
}; // WebCam

#endif
