#ifndef OPTICS_H
#define OPTICS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <iostream>
#include <cblas.h>
#include <termios.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <sys/time.h>
#include <assert.h>
//#include <WinTypes.h>
//#include <ftd2xx.h>
#include "../serial_comm.h"

namespace STOUT
{
// Class for entire optics control system
class optics_control
{

public:

  // Actuation computation function
  float* optics_compute(float x, float y);

  // Data transmission function
  void optics_transmit(double* lengths);

  // Polarizer control function
  void polarizer_rotate(char location);


private:

};
}

#endif
