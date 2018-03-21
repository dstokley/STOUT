#ifndef ADS_H
#define ADS_H

#include <stdio.h>
#include <fcntl.h>  
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include "../../serial_comm.h"

namespace STOUT {
  class ADS
  {

  public:
    // Function for reading data (azimuth and elevation angles) from ADS sensor
    float* ADS_read();

  private:

  };
}

#endif
