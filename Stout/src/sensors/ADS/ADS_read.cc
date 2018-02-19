#include "ADS_read.h"

char* ADS::ADS_read()
{

  int uart1_filestream = open(portname,O_RDWR,O_NOCTTY,O_NDELAY);

  if (uart1_filestream == -1)
  {
    //ERROR cannot open serial port
    printf("Error - Unable to open UART. Ensure it is not in use by another application\n");
  }

  //Configure the UART
  // The flags are defined in /usr/include/termios.h
  struct termios options;
  tcgetattr(uart1_filestream, &options);
  options.c_cflag = B19200 | CS8 | PARENB | CLOCAL | CREAD;
  options.c_iflag = 0;
  options.c_oflag = 0;
  options.c_lflag = 0;
  tcflush(uart1_filestream, TCIOFLUSH);
  tcsetattr(uart1_filestream, TCSANOW, &options);

  // Message to trasmit to ADS sensor to ask for data
  int tx_buffer[8] = {0x01,0x03,0x00,0x08,0x00,0x07,0x85,0xCA};
  // Write to UART1
  char tx_len = write(uart1_filestream,(void*)tx_buffer,16);

  //char rx_buffer[256];
  char *rx_buffer =(char *) malloc(sizeof(char)*255);
  //----CHECK FOR ANY RX BYTES ----
  if (uart1_filestream != -1)
  {
  //Read up to 255 characters
  	int rx_length = read(uart1_filestream, (void*)rx_buffer, 255);

  	while(rx_length < 255)
  	{
  		if (rx_length < 0)
  		{
  		std::cout << "error" << std::endl;
  		}
  		else if (rx_length == 0)
  		{
  		std::cout << "no data waiting" << std::endl;
  		}
  		else
  		{
  		rx_buffer[rx_length] = '\0';
  		printf("%i bytes read : %s\n",rx_length,rx_buffer);
  		}
  	}

  }

  close(uart1_filestream);

  return rx_buffer;
}
