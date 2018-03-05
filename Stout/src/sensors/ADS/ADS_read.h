#ifndef ADS_H
#define ADS_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

namespace STOUT {
  class ADS
  {

  public:
    // Function for reading data (azimuth and elevation angles) from ADS sensor
    void ADS_read();

  private:

  };
}

#endif
