#ifndef NIGHTOWL_HPP
#define NIGHTOWL_HPP

#include "camera/WebCam.hpp"
#include "imageproc/BackgroundSubtractor.hpp"
#include "imageproc/MotionDetector.hpp"

class Nightowl
{
public:
  Nightowl();
  ~Nightowl();

  bool run();
  bool stop();

private:
  bool shipDetection(cv::Mat frame, std::time_t timestamp);
  bool readConfigurationParameters();

  static const std::string BACKGROUND_GENERATION_TIME_CONFIG;
  static const std::string CONFIG_FILE_NAME;

  bool mRunning {false};
  BackgroundSubtractor mBackgroundSubtractor;
  WebCam mCamera;
  MotionDetector mMotionDetector;

  std::uint32_t mFrameIntervalWaitMillis {1000};

  // Configured parameters
  int mBackgroundGenerationTime {1};
  float mBackgroundGenerationImageWeight {.1};
}; // Nightowl

#endif // NIGHTOWL_HPP
