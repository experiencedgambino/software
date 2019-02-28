cmake_minimum_required (VERSION 3.0)
project (Utilities)
set (CMAKE_CXX_STANDARD 11)

add_library(utilities
   wav/WavReader.cpp
)


include_directories($Utilities_SOURCE_DIR/wav)

add_executable(Test wav/WavReaderTest.cpp)
target_link_libraries(Test utilities)
