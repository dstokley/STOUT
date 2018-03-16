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

while(1)
{
   // Trasmit data over USB
   signed char write_buffer[] = {0x01,0x03,0x00,0x08,0x00,0x07,0x85,0xCA};
   int bytes_written = 0;
   bytes_written = write(fd,write_buffer,sizeof(write_buffer));
   printf("%i Bytes Transmitted \n", bytes_written);

   // Delay for appropriate amount of time
   //usleep(5000);
   sleep(1);

   // Receive data over USB
   signed char read_buffer[19];
   int bytes_read = 0;
   bytes_read = read(fd,&read_buffer,19);
   printf("%i Bytes Received \n",bytes_read);

  int i;
  for (i=0;i<bytes_read;i++)
  {
    printf("Byte %i = %d\n",i,read_buffer[i]);
    //printf("Byte %i = %x\n",i,read_buffer[i]);
  }

// Re orintation is done here such that is matches the XY for SOUT mounting
// int x_filter_int, y_filter_int, x_nofilter_int, y_nofilter_int;
//  x_filter_int = read_buffer[9] | read_buffer[10] << 8;
//  y_filter_int = read_buffer[11] | read_buffer[12] << 8;
//  x_nofilter_int = read_buffer[13] | read_buffer[14] << 8;
//  y_nofilter_int = read_buffer[15] | read_buffer[16] << 8;

//x_filter_int = read_buffer[10] | read_buffer[9] << 8;
//y_filter_int = read_buffer[12] | read_buffer[11] << 8;
//x_nofilter_int = read_buffer[14] | read_buffer[13] << 8;
//y_nofilter_int = read_buffer[16] | read_buffer[15] << 8;


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

float x_filter, y_filter, x_nofilter, y_nofilter;
x_filter = (float)(x_filter_int_hi*255+x_filter_int_low)*0.001;
y_filter = (float)(y_filter_int_hi*255+y_filter_int_low)*0.001;
x_nofilter = (float)(x_nofilter_int_hi*255+x_nofilter_int_low)*0.001;
y_nofilter = (float)(y_nofilter_int_hi*255+y_nofilter_int_low)*0.001;


//printf("y_filter_int = %i\n",y_filter_int);


//float x_filter, y_filter, x_nofilter, y_nofilter;
// x_filter = (float)(x_filter_int)*0.01;
// y_filter = (float)(y_filter_int)*0.01;
// x_nofilter = (float)(x_nofilter_int)*0.01;
// y_nofilter = (float)(y_nofilter_int)*0.01;

//x_filter = (float)(y_filter_int)*0.0001;
//y_filter = (float)(x_filter_int)*0.0001*-1;
//x_nofilter = (float)(y_nofilter_int)*0.0001;
//y_nofilter = (float)(x_nofilter_int)*0.0001*-1;

// Print radiation Data
// int rad_int;
// rad_int = read_buffer[5] | read_buffer[6] << 8;
// //rad_int = read_buffer[5] + read_buffer[6];
// float rad;
// rad = (float)rad_int;
// printf("Radiation is %f W/m^2\n",rad);

int rad_int_low, rad_int_hi;
float rad;
rad_int_low = read_buffer[6];
rad_int_hi = read_buffer[5];
rad = (float)(rad_int_hi*255+rad_int_low);

printf("Radiation is %f W/m^2\n",rad);

// Conditionals from byte 4 data, used Data Sheet Table 6
int add_info;
add_info = read_buffer[4];
printf("Additional info = %x\n",add_info);
if (add_info == 255 ) {
  printf("Zeros Radiation or no info\n");
  x_filter = 0.0; y_filter = 0.0; x_nofilter = 0.0; y_nofilter = 0.0;
} else if (add_info == 51) {
  printf("Sun is out of FOV\n");
  x_filter = 0.0; y_filter = 0.0; x_nofilter = 0.0; y_nofilter = 0.0;
}
  else if (add_info == 1) {
  printf("Sun out of FOV, Sun is to X Positive reference\n");
  x_filter = 5.0; x_nofilter = 5.0;
}
  else if (add_info == 2) {
  printf("Sun out of FOV, Sun is to X Negative reference\n");
  x_filter = -5.0; x_nofilter = -5.0;
  }
  else if (add_info == 16) {
  printf("Sun out of FOV, Sun is to Y Positive reference\n");
  y_filter = 5.0; y_nofilter = 5.0;
}
  else if (add_info == 32) {
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




printf("With filter\n");
printf("Angle X is %f\n",x_filter);
printf("Angle Y is %f\n",y_filter);

printf("No filter\n");
printf("Angle X is %f\n",x_nofilter);
printf("Angle Y is %f\n",y_nofilter);
}
  close(fd);
}
