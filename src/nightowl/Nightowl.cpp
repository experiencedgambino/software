#include "nightowl/Nightowl.hpp"
#include "opencv2/opencv.hpp"
#include <ctime>
#include <chrono>
#include <thread>

const std::string Nightowl::CONF_NAME_BACKGROUND_GENERATION_TIME = "BackgroundGenerationTime";
const std::string Nightowl::CONF_NAME_BACKGROUND_GENERATION_IMAGE_WEIGHT = "BackgroundGenerationImageWeight";
const std::string Nightowl::CONF_NAME_FRAME_INTERVAL_WAIT_MILLIS = "FrameIntervalWaitMillis";
const std::string Nightowl::CONF_NAME_IMAGE_SAVE_DIRECTORY = "ImageSaveDirectory";
const std::string Nightowl::CONF_NAME_LOG_FILE_PATH = "LogFilePath";

// Default constructor
Nightowl::Nightowl()
{
} // Nightowl

// Default destructor
Nightowl::~Nightowl()
{

} // ~Nightowl

// Read the configuration
bool Nightowl::readConfigurationParameters(const std::string & configurationFileName)
{
    bool return_value = true;
    if (mConfiguration.parseConfig(configurationFileName) == true)
    {
      // Read background generation time
      if (mConfiguration.readParameter(CONF_NAME_BACKGROUND_GENERATION_TIME, mBackgroundGenerationTime) == false)
      {
        return_value = false;
      } // if
      
    } // if
    else
    {
      return_value = false;
    } // else
    return return_value;
} // readConfigurationParameters

// Ship the detection to the server
bool Nightowl::shipDetection(cv::Mat frame, std::time_t timestamp)
{
  bool result = cv::imwrite( "./images/" + std::to_string(timestamp) + ".jpg", frame );
  return result;
} // ship_detection

// Configure the app
bool Nightowl::configure(const std::string & configurationFileName)
{
    bool return_value = true;
    if (readConfigurationParameters(configurationFileName) == true)
    {
      // Success
    }
    else
    {
      return_value = false;
    } // else
    return return_value;
} // configure

// Run nightowl
bool Nightowl::run()
{
  mRunning = true;

  if (mCamera.open() == 0)
  {
    std::cerr << "Cannot open camera. Error" << std::endl;
    return 0;
  } // if
  else
  {
    // Generate
    cv::Mat currentFrame;
    cv::Mat grayFrame;
    currentFrame = mCamera.getFrame();
    cv::cvtColor(currentFrame, grayFrame, cv::COLOR_BGR2GRAY);
    mBackgroundSubtractor.resetBackground(grayFrame);

    std::time_t start = std::time(nullptr);
    for (;mRunning == true;)
    {
      currentFrame = mCamera.getFrame();
      mBackgroundSubtractor.addFrame(currentFrame, mBackgroundGenerationImageWeight); // Add a frame to the background subtractor
      if (std::time(nullptr) - start > mBackgroundGenerationTime)
      {
        break;
      } // if
    } // for

    // cv::namedWindow("MotionDetector", 1);
    // Motion detect
    cv::Mat frame;
    std::uint32_t count = 0;
    for (;mRunning == true;)
    {
      frame = mCamera.getFrame();
      bool motion_detected = mMotionDetector.detect(frame, mBackgroundSubtractor.getBackground());
      // cv::imshow("MotionDetector", mMotionDetector.mFrameOfInterest);
      // if (cv::waitKey(30) > 0) break;
      if (motion_detected)
      {
          std::time_t timestamp = std::time(nullptr);
          bool result = shipDetection(frame, timestamp);
          if (result == false)
          {
            std::cerr << "Cannot write image to file. Error" << std::endl;
          } // if
      } // if
      std::this_thread::sleep_for(std::chrono::milliseconds(mFrameIntervalWaitMillis));
      count++;
      mBackgroundSubtractor.addFrame(frame, .2); // Add a frame to the background subtractor
    } // for
  } // if

  mCamera.close();

  return true;
} // run

// Stop the process
bool stop()
{
  bool return_value = true;
  return return_value;
} // stop
