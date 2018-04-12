#include "ADS_read.h"

namespace STOUT
{
  float* ADS::ADS_read()
  {
    // Create comm object, open comm line
    serial_comm ADS_comm;
    int fd = ADS_comm.set_ADS_comm();
    handler handler_obj;

     // Trasmit data over USB
     unsigned char write_buffer[] = {0x01,0x03,0x00,0x08,0x00,0x07,0x85,0xCA};
     write(fd,write_buffer,sizeof(write_buffer));
     //printf("%i Bytes Transmitted \n", bytes_written);

     // Delay for appropriate amount of time (5 ms)
     usleep(20000);

     // Receive data over USB
     signed char read_buffer[19];
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
    int  x_filter_int_low, x_filter_int_hi, y_filter_int_low, y_filter_int_hi;
    int  x_nofilter_int_low, x_nofilter_int_hi, y_nofilter_int_low, y_nofilter_int_hi;
     x_filter_int_low = read_buffer[10];
     x_filter_int_hi = read_buffer[9];
     y_filter_int_low = read_buffer[12];
     y_filter_int_hi = read_buffer[11];
     x_nofilter_int_low = read_buffer[14];
     x_nofilter_int_hi = read_buffer[13];
     y_nofilter_int_low = read_buffer[16];
     y_nofilter_int_hi = read_buffer[15];
     // Angle conversions
     float x_filter_temp, y_filter_temp, x_nofilter_temp, y_nofilter_temp;
     x_filter_temp = (float)(x_filter_int_hi*255+x_filter_int_low)*0.001;
     y_filter_temp = (float)(y_filter_int_hi*255+y_filter_int_low)*0.001;
     x_nofilter_temp = (float)(x_nofilter_int_hi*255+x_nofilter_int_low)*0.001;
     y_nofilter_temp = (float)(y_nofilter_int_hi*255+y_nofilter_int_low)*0.001;

     float x_filter, y_filter, x_nofilter, y_nofilter;
     x_filter = (float)(y_filter_temp);
     y_filter = (float)(x_filter_temp)*-1;
     x_nofilter = (float)(y_nofilter_temp);
     y_nofilter = (float)(x_nofilter_temp)*-1;

     // Radiation and temperature
     // Radiation
     int rad_int_low, rad_int_hi;
     float rad;
     rad_int_low = read_buffer[6];
     rad_int_hi = read_buffer[5];
     rad = (float)(rad_int_hi*255+rad_int_low);
     // Temperature
     int temp_int_low, temp_int_hi;
     float temp;
     temp_int_low = read_buffer[8];
     temp_int_hi = read_buffer[7];
     temp = (float)(temp_int_hi*255+temp_int_low)*0.1;

     // Print current time to screen
     //std::cout << std::chrono::system_clock::now() << "\n";
     
     // Conditionals from byte 4 data, used Data Sheet Table 6
     int add_info;
     add_info = read_buffer[4];
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


     //printf("With filter\n");
     // printf("Angle X is %f\n",x_filter);
     //printf("Angle Y is %f\n",y_filter);

     //printf("No filter\n");
     //printf("Angle X is %f\n",x_nofilter);
     //printf("Angle Y is %f\n",y_nofilter);

     if (x_filter > 5.0 || y_filter > 5.0 || x_nofilter > 5.0 || y_nofilter > 5.0 || x_filter < -5.0 || y_filter < -5.0 || x_nofilter < -5.0 || y_nofilter < -5.0) {
       printf("~~~~~~~~~~~~~~~~~~~Angle outputted magnitude  is larger than 5 degrees ~~~~~~~~~~~~~~~~~~~~");
     }

     // Put needed values into the output array
     float* ADS_data = (float *) malloc(sizeof(float)*4);
     ADS_data[0] = x_filter;
     ADS_data[1] = y_filter;
     ADS_data[2] = x_nofilter;
     ADS_data[3] = y_nofilter;

     handler_obj.save_ADS_data(ADS_data, add_info);

     close(fd);

     return ADS_data;
   }



}
