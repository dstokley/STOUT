// Necessary libraries
#include "execute.h"
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <math.h>

namespace STOUT
{
  void execute::start_loop()
  {

    // System loop
    while(true)
    {
      // THESE WILL NEED TO BE HANDLED VIA INTERRUPTS
      // Read the ADS data (azimuth and elevation angles)
      //[x,y] = handler.read_ads();
      double x=0, y=0;
      double* Lengths;

      // Compute required actuation distances
      Lengths = optics.optics_compute(x,y);

      // Trasmit required actuation distances to the Arduino via Serial

      // Open serial line for Communication
      int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);

      // Error handling
      if (fd < 0)
      {
        printf("error %d opening %s: %s", errno, portname, strerror (errno));
        goto no_arduino;
      }

      // Set serial interface attributes
      optics.set_interface_attribs(fd,baud,0);

      // Configure behavior for blocking errors
      optics.set_blocking(fd,0);

      // Send actuations
      optics.optics_transmit(Lengths, fd);

      // Sensors reads and writes, heater control
      no_arduino:
      free(Lengths);    // Free dynamically allocated variable memory
    }
  }
}
