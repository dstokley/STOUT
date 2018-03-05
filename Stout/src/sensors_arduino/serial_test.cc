#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <iostream>

int main()
{
  // Communication parameters (UART)
  const char* portname = "/dev/ttyACM1";  // UART1 location

  int uart1_filestream = open(portname,O_RDWR,O_NOCTTY,O_NDELAY);

  if (uart1_filestream == -1)
  {
    //ERROR cannot open serial port
    printf("Error - Unable to open UART. Ensure it is not in use by another application\n");
    return -1;
  }
  //Configure the UART
  // The flags are defined in /usr/include/termios.h
  struct termios options;
  tcgetattr(uart1_filestream, &options);
  options.c_cflag = B115200 | CS8 | PARENB | CLOCAL | CREAD;
  options.c_iflag = 0;
  options.c_oflag = 0;
  options.c_lflag = 0;
  tcflush(uart1_filestream, TCIOFLUSH);
  tcsetattr(uart1_filestream, TCSANOW, &options);
  usleep(5000);
  //Message to trasmit to ADS sensor to ask for data
  char tx_buffer[8] = {19,96,21,12,1,4,65,34};
  // Write to UART1

  char tx_len = write(uart1_filestream,tx_buffer,8);
  usleep(5000);
  //tcflush(uart1_filestream, TCIOFLUSH);
  printf("%i bytes trasmitted \n",tx_len);
  //char rx_buffer[256];
  char rx_buffer[8];
  //Read up to 255 characters
  int rx_length;
  rx_length = read(uart1_filestream,rx_buffer,8);
  usleep(5000);
  //tcflush(uart1_filestream, TCIOFLUSH);
  printf("%i bytes received \n",rx_length);

  rx_buffer[rx_length] = '\0';
  int i;
  for (i=0;i<rx_length;i++)
  {
    printf("%i \n", rx_buffer[i]);
  }

  close(uart1_filestream);
  }
