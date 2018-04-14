#include "execute.h"

namespace STOUT
{
  int execute::start_loop()
  {
    //serial_comm comm_obj;
    handler handler_obj;
    heater_control heater_obj;
    ADS ADS_obj;
    Spectrometer spec_obj;
    //optics_control optics_obj;

    // Initialize the spectrometer
    //spec_obj.Spectrometer();

    // System loop
    while(true)
    {
      //float x = 0, y = 0;
      //float* Lengths;
      float* ADS_data;
      char* sensor_data;
      float temp_float;

      // Read the spectrometer themistor voltage
      bool status = spec_obj.ReadSpectrometerTemperature(temp_float);
      int spec_temp = (int)round(temp_float);
      //printf("Temp Spec = %i\n",spec_temp);

      // Read the ADS data
      ADS_data = ADS_obj.ADS_read();
      // Grab ADS temperature value from data
      float temp0 = ADS_data[0];
      int ADS_temp = (int)round(temp0);
      //printf("ADS Temp = %i\n",ADS_temp);

      // Compute required actuation distances
      //Lengths = Optics_obj.optics_compute(x,y);

      // Trasmit required actuation distances to the Arduino via Serial
      //Optics_obj.optics_transmit(Lengths, fd);

      // Receive data from the Arduino via serial
      sensor_data = handler_obj.receive_arduino_data();

      // Isolate heater control temperature
      int T1;
      T1 = sensor_data[0] | sensor_data[1] << 8;
      printf("Temp 1 = %i\n",T1);
      //printf("Byte 0 = %x\n",sensor_data[0]);

      // Turn heaters on/off based on temperatures
      heater_obj.heater_eval(spec_temp, T1);

      // Add spectrometer and ADS temperatures to data array
      sensor_data[22] = (char)((spec_temp)&0xFF);
      sensor_data[23] = (char)(((spec_temp>>8)&0xFF));
      sensor_data[24] = (char)(((ADS_temp>>8)&0xFF));
      sensor_data[25] = (char)(((ADS_temp>>8)&0xFF));
      //printf("Sensor data size: %lu\n",sizeof(sensor_data));

      // Save data to USB drive

      // Send EMCS data to external arduino via UART
      handler_obj.UART_transmit(sensor_data);

      // Free dynamically allocated variable memory
      //free(ADS_data);
      //free(Lengths);
      free(sensor_data);
      free(ADS_data);

      sleep(1); // Sleep for 1 second (only for TVAC testing)
    }
  }
}
