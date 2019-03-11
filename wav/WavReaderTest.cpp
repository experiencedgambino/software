#include "WavReader.hpp"
#include <iostream>

int main(int argc, char ** argv)
{
    WavReader reader;

    reader.Read(argv[1]);
    reader.GetStream(std::cout);
    reader.Write("TheOutput.wav");
} // main
