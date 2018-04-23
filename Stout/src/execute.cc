#include "execute.h"

namespace STOUT
{

  int execute::start_loop()
  {

    handler handler_obj;
    //heater_control heater_obj;
    ADS ADS_obj;
    Spectrometer spec_obj;
    //optics_control optics_obj;

    //char location = 0, home = 0;

    // FILE *f = fopen("TVAC_Data.txt", "a");
    // if (f == NULL)
    //   {
    // printf("Error opening file!\n");
    // exit(1);
    //   }
    // fprintf(f,"\nInt Temp 1\tInt Temp 2\tInt Temp 3\tInt Temp 4\tInt Temp 5\tExt Temp 1\tExt Temp 2\tPressure\tHumidity\tUDOO Temo\tSpec Temp\tADS Temp\tTime\n");
    //
    // fclose(f);

    // System loop
    while(true)
    {
      auto t1 = std::chrono::high_resolution_clock::now();
      //float x = 0, y = 0;
      float* ADS_data;
      //float* lengths;
      char* sensor_data;
      float temp_float;

      // Read the spectrometer themistor voltage
      bool status = spec_obj.ReadSpectrometerTemperature(temp_float);
      if (status != true)
      {
        continue;
      }

      int spec_temp = (int)round(temp_float);
      //printf("Temp Spec = %i\n",spec_temp);

      // Read the ADS data
      ADS_data = ADS_obj.ADS_read();

      // Grab ADS temperature value from data
      float temp0 = ADS_data[0];
      int ADS_temp = (int)round(temp0);
      // printf("ADS Temp = %i\n",ADS_temp);

      // Grab filtered angle values from data
      //x = ADS_data[1];
      //y = ADS_data[2];
      //x = 0.00;
      //y = 0.00;

      // Compute required actuation distances
      //lengths = optics_obj.optics_compute(x,y);

      // Print angles to screen
      //printf("X Angle = %f deg\nY Angle = %f deg\n",x,y);

      // Trasmit required actuation distances to the Arduino via serial line
      //optics_obj.optics_transmit(lengths);

      // Print lengths to screen
      //printf("X Length = %f mm\nY Length = %f mm\n",(float)*(lengths + 0),(float)*(lengths + 1));
      //printf("\n\n");

      // Receive data from the Arduino via serial
      sensor_data = handler_obj.receive_arduino_data();

      // Isolate heater control temperature
      //int T1;
      //T1 = sensor_data[0] | sensor_data[1] << 8;
      //int T2;
      //T2 = sensor_data[2] | sensor_data[3] << 8;
      // printf("Temp 1 = %i\n",T1);

      // Turn heaters on/off based on temperatures
      //heater_obj.heater_eval(T1, T2);

      // Add spectrometer and ADS temperatures to data array
      sensor_data[22] = (char)((spec_temp)&0xFF);
      sensor_data[23] = (char)(((spec_temp>>8)&0xFF));
      sensor_data[24] = (char)((ADS_temp)&0xFF);
      sensor_data[25] = (char)(((ADS_temp>>8)&0xFF));
      //printf("Sensor data size: %lu\n",sizeof(sensor_data));
      // for(int i=0;i<25;i++)
      // {
      //   printf("%x\n",sensor_data[i]);
      // }
      // printf("\n\n");

      // Save data to USB drive
      handler_obj.save_EMCS_data(sensor_data);
      float* angles = (float *) malloc(sizeof(float)*4);
      for(int i=0;i<5;i++)
      {
        angles[i] = {ADS_data[i+1]};
      }

      int add_info = ADS_data[5];
      //const char* save_point = "/mnt/64GB_MLC/datafile"; // Save location (USB)
      FILE *f = fopen("/mnt/mlcdrive/ADS_data/ADS_data.txt", "a");
      if (f == NULL)
      {
        printf("Error opening file!\n");
        exit(1);
      }

      /* print some text */
      //const char *text = "Write this to the file";
      //fprintf(f, "Some text: %s\n", text);

      time_t rawtime;
      struct tm * timeinfo;
      time(&rawtime);
      timeinfo = localtime(&rawtime);
      // time_t now = time(0);
      printf("%s",asctime(timeinfo));

      fprintf(f,"%f\t%f\t%f\t%f\t%x\t%s",angles[0],angles[1],angles[2],angles[3],add_info,asctime(timeinfo));


      fclose(f);
        // Send EMCS data to external arduino via UART (for TVAC testing)
        //handler_obj.UART_transmit(sensor_data);
      auto t2 = std::chrono::high_resolution_clock::now();
      std::cout << "Read and Write loop took "
              << std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count()
              << " milliseconds\n";

      // Free dynamically allocated variable memory
      free(ADS_data);
      //free(lengths);
      free(sensor_data);

      sleep(1); // Sleep for 1 second (only for TVAC testing)
    }
  }
}
