#include "ADS_read.h"
// char*
void ADS::ADS_read()
{

  int uart1_filestream = open(portname,O_RDWR,O_NOCTTY,O_NDELAY);

  if (uart1_filestream == -1)
  {
    //ERROR cannot open serial port
    printf("Error - Unable to open UART. Ensure it is not in use by another application\n");
    return;
  }
  std::cout << "DB Point 1" << std::endl;
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

  std::cout << "DB Point 2" << std::endl;
  // Message to trasmit to ADS sensor to ask for data
  int tx_buffer[8] = {0x01,0x03,0x00,0x08,0x00,0x07,0x85,0xCA};
  // Write to UART1
  char tx_len = write(uart1_filestream,tx_buffer,16);

  printf("%i bytes trasmitted \n",tx_len);
  std::cout << "DB Point 3" << std::endl;
  //char rx_buffer[256];
  usleep(10000);
  char rx_buffer[255];
  //char *rx_buffer =(char *) malloc(sizeof(char)*255);
  //----CHECK FOR ANY RX BYTES ----
  //if (uart1_filestream != -1)
  //{
    std::cout << "DB Point 4" << std::endl;
  //Read up to 255 characters
    int rx_length;
  	while ((rx_length = read(uart1_filestream,rx_buffer,255)) > 0)
    {
      std::cout << rx_length << std::endl;
  	// while(rx_length < 255)
  	// {
  	// 	if (rx_length < 0)
  	// 	{
  	// 	std::cout << "error" << std::endl;
  	// 	}
  	// 	else if (rx_length == 0)
  	// 	{
  	// 	std::cout << "no data waiting" << std::endl;
  	// 	}
  	// 	else
  	// 	{
      std::cout << "DB Point 5" << std::endl;
		  rx_buffer[rx_length] = '\0';
		  printf("%i bytes read \n",rx_length);
  	// 	}
  	// }

  //}
    }

  close(uart1_filestream);
  //return rx_buffer;
}
