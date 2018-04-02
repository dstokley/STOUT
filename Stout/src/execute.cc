#include "execute.h"
// #include <unistd.h>
// #include <iostream>
// #include <fcntl.h>
// #include <stdio.h>
// #include <chrono>
// #include <math.h>

namespace STOUT
{
  int execute::start_loop()
  {
    serial_comm comm_obj;
    handler handler_obj;
    optics_control optics_obj;
    heater_control heater_obj;

    float x = 0, y = 0;
    float* Lengths;
    float* ADS_data;
    char* sensor_data;

    //float temp;
    //bool status;
    int count = 0;      // Count for deterimining when to transmit sensor data over UART

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

      // Setup arduino communication
      int arduino_status = comm_obj.set_arduino_comm();

      if (arduino_status == 0)
      {
        // Receive data from the Arduino via serial
        sensor_data = handler_obj.receive_arduino_data();
      }
      else
      {
        continue; // Jump to start of loop in arduino connection not acheived
      }

      // Isolate heater control temperatures
      int T1, T2;
      T1 = sensor_data[0] | sensor_data[1] << 8;
      T2 = sensor_data[2] | sensor_data[3] << 8;

      // Turn heaters on/off based on temperatures
      heater_obj.heater_eval(T1, T2);

      // Save data to USB drive


      // Used for sending data over UART for testing
      count = count + 1;
      if (count == 30)
      {
        int UART_status = comm_obj.set_UART_comm();
        if (UART_status == 0)
        {
          handler_obj.UART_transmit(sensor_data);
          count = 0;
        }
      }

      // Free dynamically allocated variable memory
      //free(ADS_data);
      //free(Lengths);
      free(sensor_data);
    }
  }
}
