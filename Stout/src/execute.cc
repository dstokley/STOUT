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
    double x=0, y=0;
    double* Lengths;
    //char* Angles;

    // Open serial line for Communication
    int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);

    // Error handling
    if (fd < 0)
    {
      printf("error %d opening %s: %s", errno, portname, strerror (errno));
    }

    // Set serial interface attributes
    optics.set_interface_attribs(fd,baud,0);

    // Configure behavior for blocking errors
    optics.set_blocking(fd,0);

    // System loop
    while(true)
    {
      // THESE WILL NEED TO BE HANDLED VIA INTERRUPTS

      // Read the ADS data (azimuth and elevation angles)
      //Angles = ADS_obj.ADS_read();

      // Compute required actuation distances
      Lengths = optics.optics_compute(x,y);

      // Trasmit required actuation distances to the Arduino via Serial
      optics.optics_transmit(Lengths, fd);

      // Receive data from the Arduino via serial
      

      // Sensors reads and writes, heater control
      free(Lengths);    // Free dynamically allocated variable memory
    }
  }
}
