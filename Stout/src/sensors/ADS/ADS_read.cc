#include "ADS_read.h"

namespace STOUT
{
  float* ADS::ADS_read()
  {

    // Open USB line
    int fd;
    fd = open("/dev/ttyUSB0",O_RDWR | O_NOCTTY);
    if (fd==1)
    {
       printf("Error! in Opening ttyUSB0\n");
     }
    else
    {
       printf("ttyUSB0 Opened Successfully\n");
     }

     // Setup port settings
     struct termios options;
     tcgetattr(fd, &options);
     tcsetattr(fd,TCSANOW,&options);

     // Trasmit data over USB
     unsigned char write_buffer[] = {0x01,0x03,0x00,0x08,0x00,0x07,0x85,0xCA};
     int bytes_written = 0;
     bytes_written = write(fd,write_buffer,sizeof(write_buffer));
     printf("%i Bytes Transmitted \n", bytes_written);

     // Delay for appropriate amount of time
     usleep(5000);

     // Receive data over USB
     unsigned char read_buffer[19];
     int bytes_read = 0;
     bytes_read = read(fd,&read_buffer,19);
     printf("%i Bytes Received \n",bytes_read);

     // Printing received values
     int i;
     for (i=0;i<19;i++)
     {
       printf("Byte %i = %0x\n",i,read_buffer[i]);
     }

     // Convert received bytes to desired data values
     int ADS_rad_int, ADS_temp_int, x_filter_int, y_filter_int, x_nofilter_int, y_nofilter_int;
     //ADS_rad_int = read_buffer[5] | read_buffer[6] << 8;
     ADS_temp_int = read_buffer[7] | read_buffer[8] << 8;
     x_filter_int = read_buffer[9] | read_buffer[10] << 8;
     y_filter_int = read_buffer[11] | read_buffer[12] << 8;
     //x_nofilter_int = read_buffer[13] | read_buffer[14] << 8;
     //y_nofilter_int = read_buffer[15] | read_buffer[16] << 8;

     float ADS_rad, ADS_temp, x_filter, y_filter, x_nofilter, y_nofilter;
     //ADS_rad = (float)(ADS_rad_int);
     ADS_temp = (float)(ADS_temp_int)*0.1;
     x_filter = (float)(x_filter_int)*0.0001;
     y_filter = (float)(y_filter_int)*0.0001;
     //x_nofilter = (float)(x_nofilter_int)*0.001;
     //y_nofilter = (float)(y_nofilter_int)*0.001;

     float* ADS_data = (float *) malloc(sizeof(float)*3);
     ADS_data[0] = ADS_temp;
     ADS_data[1] = x_filter;
     ADS_data[2] = y_filter;

     close(fd);

     return ADS_data;
   }



}
