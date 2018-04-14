#include "ADS_read.h"

namespace STOUT
{
  float* ADS::ADS_read()
  {
    // Create comm object, open comm line
    serial_comm ADS_comm;
    int fd = ADS_comm.set_ADS_comm();

     // Trasmit data over USB
     unsigned char write_buffer[] = {0x01,0x03,0x00,0x08,0x00,0x07,0x85,0xCA};
     write(fd,write_buffer,sizeof(write_buffer));
     //printf("%i Bytes Transmitted \n", bytes_written);

     // Delay for appropriate amount of time (5 ms)
     usleep(5000);

     // Receive data over USB
     char read_buffer[19];
     read(fd,&read_buffer,19);
     //printf("%i Bytes Received \n",bytes_read);

     // Printing received values
     // int i;
     // for (i=0;i<19;i++)
     // {
     //   printf("Byte %i = %0x\n",i,read_buffer[i]);
     // }

     // Convert received bytes to desired data values
     // Angles
     int x_filter_int_low, x_filter_int_hi, y_filter_int_low, y_filter_int_hi;
     int x_nofilter_int_low, x_nofilter_int_hi, y_nofilter_int_low, y_nofilter_int_hi;
     x_filter_int_low = read_buffer[10];
     x_filter_int_hi = read_buffer[9];
     y_filter_int_low = read_buffer[12];
     y_filter_int_hi = read_buffer[11];
     x_nofilter_int_low = read_buffer[14];
     x_nofilter_int_hi = read_buffer[13];
     y_nofilter_int_low = read_buffer[16];
     y_nofilter_int_hi = read_buffer[15];
     // Angle conversions
     float x_filter, y_filter, x_nofilter, y_nofilter;
     x_filter = (float)(x_filter_int_hi*255+x_filter_int_low)*0.001;
     y_filter = (float)(y_filter_int_hi*255+y_filter_int_low)*0.001;
     x_nofilter = (float)(x_nofilter_int_hi*255+x_nofilter_int_low)*0.001;
     y_nofilter = (float)(y_nofilter_int_hi*255+y_nofilter_int_low)*0.001;

     // Radiation and temperature
     // Radiation
     int rad_int_low, rad_int_hi;
     float rad;
     rad_int_low = read_buffer[6];
     rad_int_hi = read_buffer[5];
     rad = (float)(rad_int_hi*255+rad_int_low);
     // Temperature
     unsigned char temp_low, temp_hi;
     signed int temp_int;
     float temp;
     temp_low = read_buffer[8];
     temp_hi = read_buffer[7];
     temp_int = (temp_hi << 8) + temp_low;
     temp = (float)temp_int*0.1;
     //temp = (float)(temp_int_hi*255+temp_int_low)*0.1;

     // Put needed values into the output array
     float* ADS_data = (float *) malloc(sizeof(float)*3);
     ADS_data[0] = temp;
     ADS_data[1] = x_filter;
     ADS_data[2] = y_filter;

     close(fd);

     return ADS_data;
   }



}
