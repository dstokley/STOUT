// Necessary libraries
#include "execute.h"
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <stdio.h>
#include <chrono>
#include <math.h>

namespace STOUT
{
  int execute::start_loop()
  {
    serial_comm Comm_obj;
    heater_control Heater_obj;
    handler Handler_obj;

    // double x=0, y=0;
    // double* Lengths;
    // float* ADS_data;
    char* Sensor_data;
    // const char* portname = "/dev/ttyACM0";  // Arduino location
    //
    // // Setup serial communication with Arduino
    // int fd = open (portname, O_RDWR | O_NOCTTY | O_SYNC);
    // if (fd < 0)
  	// {
  	// 		printf("error %d opening %s\n", errno, portname);
  	// 		return -1;
  	// }
    // Comm_obj.set_interface_attribs (fd, 115200, 0);		// Set speed to 115,200 bps, 8n1 (no parity)
  	// Comm_obj.set_blocking (fd, 0);						          // Set no blocking
    //float temp;
    //bool status;
    int count = 0;  // Count for deterimining when to transmit sensor data over UART
    // System loop
    while(true)
    {
      // status = Spec_obj.ReadSpectrometerTemperature(temp);
      // printf("Spectrometer Temp = %f \n", temp);
      // sleep(10);
      // THESE WILL NEED TO BE HANDLED VIA INTERRUPTS

      // Read the ADS data (azimuth and elevation angles)
      //ADS_data = ADS_obj.ADS_read();

      // Compute required actuation distances
      //Lengths = Optics_obj.optics_compute(x,y);

      // Trasmit required actuation distances to the Arduino via Serial
      //Optics_obj.optics_transmit(Lengths, fd);

      // Receive data from the Arduino via serial
      Sensor_data = Handler_obj.receive_arduino_data();

      // Isolate heater control temperatures
      int T1, T2;
      T1 = Sensor_data[0] | Sensor_data[1] << 8;
      T2 = Sensor_data[2] | Sensor_data[3] << 8;

      // Save data to USB drive

      // Turn heaters on/off based on temperatures
      Heater_obj.heater_eval(T1, T2);

      count = count + 1;

      if (count == 30)
      {
        Handler_obj.UART_transmit(Sensor_data);
        count = 0;
      }

      sleep(1);
      // Free dynamically allocated variable memory
      //free(ADS_data);
      //free(Lengths);
      free(Sensor_data);
      // return status;
    }
  }
}
