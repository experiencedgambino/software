cmake_minimum_required (VERSION 2.8)
project (Utilities)
set (CMAKE_CXX_STANDARD 11)

set (src_directory ${Utilities_SOURCE_DIR}/src)

add_library(utilities
   ${src_directory}/wav/WavReader.cpp
   ${src_directory}/audiostream/AudioStreamPulseAudio.cpp
)

add_library(nightowl
   ${src_directory}/imageproc/MotionDetector.cpp
   ${src_directory}/nightowl/Nightowl.cpp
   ${src_directory}/imageproc/BackgroundSubtractor.cpp
   ${src_directory}/camera/WebCam.cpp
)

find_package(OpenCV REQUIRED)

include_directories(${src_directory})

add_executable(WaveTester ${src_directory}/wav/WavReaderTest.cpp)
add_executable(AudioStreamTest ${src_directory}/audiostream/AudioStreamPulseAudioTest.cpp)
add_executable(NightowlTest ${src_directory}/nightowl/NightowlTest.cpp)
target_link_libraries(WaveTester utilities)
target_link_libraries(AudioStreamTest utilities)
target_link_libraries(nightowl opencv_core)
target_link_libraries(nightowl opencv_highgui)
target_link_libraries(NightowlTest nightowl)
