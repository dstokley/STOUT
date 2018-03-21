#include <stdio.h>
#include <fcntl.h>  /* File Control Definitions          */
#include <termios.h>/* POSIX Terminal Control Definitions*/
#include <unistd.h> /* UNIX Standard Definitions         */
#include <errno.h>  /* ERROR Number Definitions          */
int main()
{
  // Open USB line
  int fd;
  fd = open("/dev/ttyACM0",O_RDWR | O_NOCTTY);
  if (fd==1)
  {
     printf("Error! in Opening ACM0\n");
   }
  else
  {
     printf("ACM0 Opened Successfully\n");
   }

   // Setup port settings
   struct termios options;
   tcgetattr(fd, &options);
   tcsetattr(fd,TCSANOW,&options);

   // Trasmit data over UART
   // unsigned char write_buffer[] = {1,2,3,4};
   // int bytes_written = 0;
   // bytes_written = write(fd,write_buffer,sizeof(write_buffer));
   // printf("%i Bytes Transmitted \n", bytes_written);

   // Delay for appropriate amount of time
   //usleep(5000);

  //  // Receive data over USB
   unsigned char read_buffer[8];
   int bytes_read = 0;
   bytes_read = read(fd,&read_buffer,8);
   usleep(5000);
   printf("%i Bytes Received \n",bytes_read);

   if (bytes_read >0)
   {
  int i;
  for (i=0;i<bytes_read;i++)
  {
    //printf("Byte %i = %x\n",i,read_buffer[i]);
    printf("Byte %i = %x\n",i,read_buffer[i]);
  }
}

  close(fd);
  return 0;
}
