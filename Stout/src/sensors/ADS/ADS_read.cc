#include "ADS_read.h"

namespace STOUT
{
  float* ADS::ADS_read()
  {
    // Create comm object, open comm line
    serial_comm ADS_comm;
    handler ADS_handler;
    int fd = ADS_comm.set_ADS_comm();

     // Trasmit data over USB
     unsigned char write_buffer[] = {0x01,0x03,0x00,0x08,0x00,0x07,0x85,0xCA};
     write(fd,write_buffer,sizeof(write_buffer));
     //printf("%i Bytes Transmitted \n", bytes_written);

     // Delay for appropriate amount of time
     usleep(35000);

     // Receive data over USB
     signed char read_buffer[19];
     read(fd,&read_buffer,19);
     usleep(2000);
     tcflush(fd,TCIOFLUSH);

     //printf("%i Bytes Received \n",bytes_read);
     //Printing received values
     // int i;
     // for (i=0;i<bytes_read;i++)
     // {
     //   printf("Byte %i = %0x\n",i,read_buffer[i]);
     // }

     // Get integer angle values from returned message
     signed int x_filter_int, y_filter_int, x_nofilter_int, y_nofilter_int;
     x_filter_int = (read_buffer[9] << 8) + read_buffer[10];
     y_filter_int = (read_buffer[11] << 8) + read_buffer[12];
     x_nofilter_int = (read_buffer[13] << 8) + read_buffer[14];
     y_nofilter_int = (read_buffer[15] << 8) + read_buffer[16];

     // Convert integer angles to actual, float angles
     float x_filter_temp, y_filter_temp, x_nofilter_temp, y_nofilter_temp;
     x_filter_temp = (float)x_filter_int*0.001;
     y_filter_temp = (float)y_filter_int*0.001;
     x_nofilter_temp = (float)x_nofilter_int*0.001;
     y_nofilter_temp = (float)y_nofilter_int*0.001;

     // Adjust axes according to optical axis
     float x_filter, y_filter, x_nofilter, y_nofilter;
     x_filter = y_filter_temp*-1;
     y_filter = x_filter_temp;
     x_nofilter = y_nofilter_temp*-1;
     y_nofilter = x_nofilter_temp;

     // Print ADS angle values
     printf("X filtered = %f\nY filtered = %f\nX unfiltered = %f\nY unfiltered = %f\n\n\n",x_filter,y_filter,x_nofilter,y_nofilter);

     // Radiation and temperature

     // Radiation
     // unsigned char rad_low, rad_hi;
     // signed int rad_int;
     // float rad;
     // rad_low = read_buffer[6];
     // rad_hi = read_buffer[5];
     // rad_int = (rad_hi << 8) + rad_low;
     // rad = (float)rad_int;

     // Temperature
     unsigned char temp_low, temp_hi;
     signed int temp_int;
     float temp;
     temp_low = read_buffer[8];
     temp_hi = read_buffer[7];
     temp_int = (temp_hi << 8) + temp_low;
     temp = (float)temp_int*0.1;

     // Additional information
      unsigned char add_info;
      add_info = (unsigned char)read_buffer[4];
      printf("Additional info = %x\n",add_info);
      if (add_info == 255 ) {
        printf("Zero Radiation or no info\n");
        x_filter = 0.0; y_filter = 0.0; x_nofilter = 0.0; y_nofilter = 0.0;
      }
      else if (add_info == 51) {
        printf("Sun is out of FOV\n");
        x_filter = 0.0; y_filter = 0.0; x_nofilter = 0.0; y_nofilter = 0.0;
      }
      else if (add_info == 1) {
        printf("Sun out of FOV, Sun is to X Positive reference\n");
        x_filter = 5.0; x_nofilter = 5.0;
      }
      else if (add_info == 2 || x_filter < -5.0 || x_nofilter < -5.0) {
        printf("Sun out of FOV, Sun is to X Negative reference\n");
        x_filter = -5.0; x_nofilter = -5.0;
      }
      else if (add_info == 16) {
        printf("Sun out of FOV, Sun is to Y Positive reference\n");
        y_filter = 5.0; y_nofilter = 5.0;
      }
      else if (add_info == 32 || y_filter < -5.0 || y_nofilter < -5.0) {
        printf("Sun out of FOV, Sun is to Y Negative reference\n");
        y_filter = -5.0; y_nofilter = -5.0;
      }
      else if (add_info == 17) {
        printf("Sun out of FOV, Sun is to X Positive and Y Positve reference\n");
        x_filter = 5.0; y_filter = 5.0; x_nofilter = 5.0; y_nofilter = 5.0;
      }
      else if (add_info == 18) {
        printf("Sun out of FOV, Sun is to X Negative and Y Positve reference\n");
        x_filter = -5.0; y_filter = 5.0; x_nofilter = -5.0; y_nofilter = 5.0;
      }
      else if (add_info == 33) {
        printf("Sun out of FOV, Sun is to X Positive and Y Negative reference\n");
        x_filter = 5.0; y_filter = -5.0; x_nofilter = 5.0; y_nofilter = -5.0;
      }
      else if (add_info == 34) {
        printf("Sun out of FOV, Sun is to X Negative and Y Negative reference\n");
        x_filter = -5.0; y_filter = -5.0; x_nofilter = -5.0; y_nofilter = -5.0;
      }

     // Put needed values into the output array
     float* ADS_data = (float *) malloc(sizeof(float)*5);
     ADS_data[0] = temp;
     ADS_data[1] = x_filter;
     ADS_data[2] = y_filter;
     ADS_data[3] = x_nofilter;
     ADS_data[4] = y_nofilter;

     // Save values
     ADS_handler.save_ADS_data(ADS_data, add_info);

     // Close serial connection
     close(fd);

     return ADS_data;
   }

}
