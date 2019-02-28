#include "WavReader.hpp"

int main(int argc, char ** argv)
{
    WavReader reader;

    reader.Read(argv[1]);
    reader.Write("TheOutput.wav");
} // main
