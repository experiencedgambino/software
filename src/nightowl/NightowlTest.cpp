#include "nightowl/Nightowl.hpp"

int main(int argc, char ** argv)
{
    Nightowl * nightowlProcess = new Nightowl();
    int return_value = 0;
    const int NUMBER_OF_TOTAL_ARGUMENTS = 2;
    const int NIGHTOWL_CONFIGURATION_ARGUMENT = 1;
    if (NUMBER_OF_TOTAL_ARGUMENTS == argc)
    {
        if (nightowlProcess->configure(argv[NIGHTOWL_CONFIGURATION_ARGUMENT]) == true)
        {
            return_value = nightowlProcess->run();
        } // if
        else
        {
            std::cout << "Failed to configure Nightowl." << std::endl;
            return_value = 1;
        } // else
    } // if

    return return_value;
} // main
