#include "nightowl/Nightowl.hpp"

int main()
{
  Nightowl * nightowlProcess = new Nightowl();

  bool results = nightowlProcess->run();

  if (!results)
  {
    return 1;
  } // if

  return 0;
} // main
