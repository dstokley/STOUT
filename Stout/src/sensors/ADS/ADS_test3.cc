#include <stdio.h>
#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <unistd.h> /* UNIX Standard Definitions         */
#include <errno.h>  /* ERROR Number Definitions          */
int main()
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

  int i;
  for (i=0;i<19;i++)
  {
    //printf("Byte %i = %x\n",i,read_buffer[i]);
    printf("Byte %i = %i\n",i,read_buffer[i]);
  }

// Re orintation is done here such that is matches the XY for SOUT mounting
int x_filter_int, y_filter_int, x_nofilter_int, y_nofilter_int;
y_filter_int = read_buffer[9] | read_buffer[10] << 8;
x_filter_int = read_buffer[11] | read_buffer[12] << 8;
x_nofilter_int = read_buffer[13] | read_buffer[14] << 8;
y_nofilter_int = read_buffer[15] | read_buffer[16] << 8;


float x_filter, y_filter, x_nofilter, y_nofilter;
x_filter = (float)(x_filter_int)*0.0001;
y_filter = (float)(y_filter_int)*0.0001*-1;
x_nofilter = (float)(x_nofilter_int)*0.0001;
y_nofilter = (float)(y_nofilter_int)*0.0001*-1;

printf("With filter\n");
printf("Angle X is %f\n",x_filter);
printf("Angle Y is %f\n",y_filter);

printf("No filter\n");
printf("Angle X is %f\n",x_nofilter);
printf("Angle Y is %f\n",y_nofilter);
  close(fd);
}
