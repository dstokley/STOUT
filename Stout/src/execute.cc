#include "execute.h"

namespace STOUT
{
  int execute::start_loop()
  {
    //serial_comm comm_obj;
    handler handler_obj;
    //heater_control heater_obj;
    ADS ADS_obj;
    //Spectrometer spec_obj;
    //optics_control optics_obj;

    // Initialize the spectrometer
    //spec_obj.Spectrometer();

    // System loop
    while(true)
    {
      //float x = 0, y = 0;
      //float* Lengths;
      float* ADS_data;
      //char* sensor_data;
      //float temp_float;

      // Read the spectrometer themistor voltage
      //bool status = spec_obj.ReadSpectrometerTemperature(temp_float);
      //int spec_temp = (int)round(temp_float);

      // Read the ADS data
      ADS_data = ADS_obj.ADS_read();
      // Grab ADS temperature value from data
      printf("x filter = %f\n",ADS_data[0]);
      printf("y filter = %f\n",ADS_data[1]);
      printf("x no filter = %f\n",ADS_data[2]);
      printf("y no filter = %f\n\n\n",ADS_data[3]);
      
      //int ADS_temp = (int)round(temp0);

      // Compute required actuation distances
      //Lengths = Optics_obj.optics_compute(x,y);

      // Trasmit required actuation distances to the Arduino via Serial
      //Optics_obj.optics_transmit(Lengths, fd);

      // Receive data from the Arduino via serial
      //sensor_data = handler_obj.receive_arduino_data();

      // Isolate heater control temperature
      //int T1;
      //T1 = sensor_data[0] | sensor_data[1] << 8;

      // Turn heaters on/off based on temperatures
      //heater_obj.heater_eval(spec_temp, T1);

      // Add spectrometer and ADS temperatures to data array
      //sensor_data[22] = (char)((spec_temp)&0xFF);
      //sensor_data[23] = (char)(((spec_temp>>8)&0xFF));
      //sensor_data[24] = (char)(((ADS_temp>>8)&0xFF));
      //sensor_data[25] = (char)(((ADS_temp>>8)&0xFF));

      // Save data to USB drive

      // Convert from float to chars
      unsigned char * angle1 = (unsigned char*) &ADS_data[0];
      unsigned char * angle2 = (unsigned char*) &ADS_data[1];
      unsigned char * angle3 = (unsigned char*) &ADS_data[2];
      unsigned char * angle4 = (unsigned char*) &ADS_data[3];

      //printf("Angle 1 is size: %i \n", strlen(angle1));
      unsigned char data[16];
      memcpy(data,angle1,sizeof(angle1));
      memcpy(data+sizeof(angle1),angle2,sizeof(angle2));
      memcpy(data+sizeof(angle1)+sizeof(angle2),angle3,sizeof(angle3));
      

      // Send EMCS data to external arduino via UART
      //handler_obj.UART_transmit(sensor_data);
      //handler_obj.UART_transmit(ADS_data);
      //printf("ADS DATA 1 is: %f\n", ADS_data[0]);
       for (std::size_t i = 0; i != sizeof(data); ++i)
	{
	  std::printf("The byte in EXECUTE: #%zu is 0x%02X\n", i, data[i]);
	}
       
       //std::printf("THE DATA STRING IS: 0X");
       //for (std::size_t i = 0; i != sizeof(data); ++i)
       //{
       //  std::printf("%02X", i, angle1[i]);
       //	}
       //std::printf("\n");
     
      handler_obj.UART_transmit(data);
      usleep(1000);
      
      
      // Free dynamically allocated variable memory
      //free(ADS_data);
      //free(Lengths);
      //free(sensor_data);
      free(ADS_data);

      //sleep(1); // Sleep for 1 second (only for TVAC testing)
    }
  }
}
