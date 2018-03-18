// Necessary libraries
#include "execute.h"
#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <chrono>
#include <math.h>

namespace STOUT
{
  int execute::start_loop()
  {
    // double x=0, y=0;
    // double* Lengths;
    // float* ADS_data;
    // char* sensor_data;
    // const char* portname = "/dev/ttyACM0";  // Arduino location
    //
    // // Setup serial communication with Arduino
    // int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
    // if (fd < 0)
  	// {
  	// 		printf("error %d opening %s: %s", errno, portname, strerror (errno));
  	// 		return -1;
  	// }
    // comm_obj.set_interface_attribs (fd, B115200, 0);		// Set speed to 115,200 bps, 8n1 (no parity)
  	// comm_obj.set_blocking (fd, 0);						          // Set no blocking
    float temp;
    bool status;
    // System loop
    while(true)
    {
      // status = Spec_obj.ReadSpectrometerTemperature(temp);
      // printf("Spectrometer Temp = %f \n", temp);
      // sleep(10);
      // THESE WILL NEED TO BE HANDLED VIA INTERRUPTS

      // Read the ADS data (azimuth and elevation angles)
      ADS_data = ADS_obj.ADS_read();

      // Compute required actuation distances
      Lengths = Optics_obj.optics_compute(x,y);

      // Trasmit required actuation distances to the Arduino via Serial
      Optics_obj.optics_transmit(Lengths, fd);

      // Receive data from the Arduino via serial
      Sensor_data = Handler_obj.receive_arduino_data(fd);

      // Call Handler_obj function to collect control temperatures(T1, T2)

      // Turn heaters on/off based on temperatures
      //Heater_obj.heater_eval(T1, T2);

      // Free dynamically allocated variable memory
      free(ADS_data);
      free(Lengths);
      free(Sensor_data);
      // return status;
    }
  }
}
