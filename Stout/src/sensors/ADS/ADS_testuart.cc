#include <stdio.h>
#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <unistd.h> /* UNIX Standard Definitions         */
#include <errno.h>  /* ERROR Number Definitions          */
int main()
{
  // Open USB line
  int fd;
  fd = open("/dev/ttyS5",O_RDWR | O_NOCTTY);
  if (fd==1)
  {
     printf("Error! in Opening ttyS5\n");
   }
  else
  {
     printf("ttyS5 Opened Successfully\n");
   }

   // Setup port settings
   struct termios options;
   tcgetattr(fd, &options);
   tcsetattr(fd,TCSANOW,&options);

   while(1)
   {
   // Trasmit data over USB
   unsigned char write_buffer[] = {12, 13};
   //unsigned char write_buffer[] = {1,2,3,1,5,4,8,9,6,10,14,54,12,1,1,2,3,8,7,5};
   int bytes_written = 0;
   bytes_written = write(fd,write_buffer,sizeof(write_buffer));
   printf("%i Bytes Transmitted \n", bytes_written);

   // Delay for appropriate amount of time
   //usleep(5000);
   sleep(1);
 }

  //  // Receive data over USB
  //  unsigned char read_buffer[19];
  //  int bytes_read = 0;
  //  bytes_read = read(fd,&read_buffer,19);
  //  printf("%i Bytes Received \n",bytes_read);
  //
  // int i;
  // for (i=0;i<bytes_read;i++)
  // {
  //   //printf("Byte %i = %x\n",i,read_buffer[i]);
  //   printf("Byte %i = %x\n",i,read_buffer[i]);
  // }

// // Re orintation is done here such that is matches the XY for SOUT mounting
// int x_filter_int, y_filter_int, x_nofilter_int, y_nofilter_int;
// //x_filter_int = read_buffer[9] | read_buffer[10] << 8;
// //y_filter_int = read_buffer[11] | read_buffer[12] << 8;
// //x_nofilter_int = read_buffer[13] | read_buffer[14] << 8;
// //y_nofilter_int = read_buffer[15] | read_buffer[16] << 8;
//
// x_filter_int = read_buffer[10] | read_buffer[9] << 8;
// y_filter_int = read_buffer[12] | read_buffer[11] << 8;
// x_nofilter_int = read_buffer[14] | read_buffer[13] << 8;
// y_nofilter_int = read_buffer[16] | read_buffer[15] << 8;
//
// printf("x_filter_int = %x\n",x_filter_int);
//
//
// float x_filter, y_filter, x_nofilter, y_nofilter;
// x_filter = (float)(x_filter_int)*0.0001;
// y_filter = (float)(y_filter_int)*0.0001;
// x_nofilter = (float)(x_nofilter_int)*0.0001;
// y_nofilter = (float)(y_nofilter_int)*0.0001;
//
// // Print radiation Data
// int rad_int;
// rad_int = read_buffer[5] | read_buffer[6] << 8;
// float rad;
// rad = (float)rad_int;
// printf("Radiation is %f W/m^2\n",rad);
//
// // Conditionals from byte 4 data, used Data Sheet Table 6
// int add_info;
// add_info = read_buffer[4];
// printf("Additional info = %x\n",add_info);
// if (add_info == 255) {
//   printf("Zeros Radiation or no info\n");
//   x_filter = 0.0; y_filter = 0.0; x_nofilter = 0.0; y_nofilter = 0.0;
// } else if (add_info == 51) {
//   printf("Sun is out of FOV\n");
//   x_filter = 0.0; y_filter = 0.0; x_nofilter = 0.0; y_nofilter = 0.0;
// }
//   else if (add_info == 1) {
//   printf("Sun out of FOV, Sun is to X Positive reference\n");
//   x_filter = 0.0; y_filter = 0.0; x_nofilter = 0.0; y_nofilter = 0.0;
// }
//   else if (add_info == 2) {
//   printf("Sun out of FOV, Sun is to X Negative reference\n");
//   x_filter = 0.0; y_filter = 0.0; x_nofilter = 0.0; y_nofilter = 0.0;
//   }
//   else if (add_info == 16) {
//   printf("Sun out of FOV, Sun is to Y Positive reference\n");
//   x_filter = 0.0; y_filter = 0.0; x_nofilter = 0.0; y_nofilter = 0.0;
// }
//   else if (add_info == 32) {
//   printf("Sun out of FOV, Sun is to Y Negative reference\n");
//   x_filter = 0.0; y_filter = 0.0; x_nofilter = 0.0; y_nofilter = 0.0;
//   }
//   else if (add_info == 17) {
//   printf("Sun out of FOV, Sun is to X Positive and Y Positve reference\n");
//   x_filter = 0.0; y_filter = 0.0; x_nofilter = 0.0; y_nofilter = 0.0;
// }
//   else if (add_info == 18) {
//   printf("Sun out of FOV, Sun is to X Negative and Y Positve reference\n");
//   x_filter = 0.0; y_filter = 0.0; x_nofilter = 0.0; y_nofilter = 0.0;
//   }
//   else if (add_info == 33) {
//   printf("Sun out of FOV, Sun is to X Positive and Y Negative reference\n");
//   x_filter = 0.0; y_filter = 0.0; x_nofilter = 0.0; y_nofilter = 0.0;
// }
//   else if (add_info == 34) {
//   printf("Sun out of FOV, Sun is to X Negative and Y Negative reference\n");
//   x_filter = 0.0; y_filter = 0.0; x_nofilter = 0.0; y_nofilter = 0.0;
//   }
//
//
//
//
// printf("With filter\n");
// printf("Angle X is %f\n",x_filter);
// printf("Angle Y is %f\n",y_filter);
//
// printf("No filter\n");
// printf("Angle X is %f\n",x_nofilter);
// printf("Angle Y is %f\n",y_nofilter);
  close(fd);
}
