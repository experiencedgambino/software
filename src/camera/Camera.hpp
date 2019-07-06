#ifndef CAMERA_CAMERA_HPP
#define CAMERA_CAMERA_HPP

#include "opencv/cv.h"

class Camera
{
public:
    // Grabs the next frame
    virtual bool getFrame(cv::Mat & frame) = 0;

    // Initializes the camera
    virtual bool open() = 0;

    // Closes the camera
    virtual bool close() = 0;

};

#endif // CAMERA_CAMERA_HPP
