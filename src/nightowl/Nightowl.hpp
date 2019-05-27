#ifndef NIGHTOWL_HPP
#define NIGHTOWL_HPP

#include "camera/WebCam.hpp"
#include "configuration/Configuration.hpp"
#include "imageproc/BackgroundSubtractor.hpp"
#include "imageproc/MotionDetector.hpp"

class Nightowl
{
public:
    Nightowl();
    ~Nightowl();

    bool configure(const std::string & configurationFileName);
    bool run();
    bool stop();

private:
    bool shipDetection(cv::Mat frame, std::time_t timestamp);
    bool readConfigurationParameters(const std::string & configurationFileName);

    bool mRunning {false};
    BackgroundSubtractor mBackgroundSubtractor {};
    WebCam mCamera {};
    MotionDetector mMotionDetector {};
    Configuration mConfiguration {};

    // Configuration parameter name
    static const std::string CONF_NAME_BACKGROUND_GENERATION_TIME;
    static const std::string CONF_NAME_BACKGROUND_GENERATION_IMAGE_WEIGHT;
    static const std::string CONF_NAME_FRAME_INTERVAL_WAIT_MILLIS;
    static const std::string CONF_NAME_IMAGE_SAVE_DIRECTORY;
    static const std::string CONF_NAME_LOG_FILE_PATH;
    static const std::string CONF_NAME_VERBOSE_MODE;
    // Configuration parameters
    int mBackgroundGenerationTime {1};
    float mBackgroundGenerationImageWeight {.1};
    std::uint32_t mFrameIntervalWaitMillis {1000};
    std::string mImageSaveDirectory {};
    std::string mLogFilePath {};
    bool mVerboseMode {false};
}; // Nightowl

#endif // NIGHTOWL_HPP
