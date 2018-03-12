#ifndef ADS_H
#define ADS_H

#include <stdio.h>
#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <unistd.h> /* UNIX Standard Definitions         */
#include <errno.h>  /* ERROR Number Definitions          */
#include <stdlib.h>

namespace STOUT {
  class ADS
  {

  public:
    // Function for reading data (azimuth and elevation angles) from ADS sensor
    float* ADS_read();
    // class ADS_data
    // {
    //   float ADS_rad;
    //   float ADS_temp;
    //   float x_filter;
    //   float y_filter;
    //   float x_nofilter;
    //   float y_nofilter;
    // };

  private:

  };
}

#endif
