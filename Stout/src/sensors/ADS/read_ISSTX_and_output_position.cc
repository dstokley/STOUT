#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

using namespace std;

int main(int argc, char** argv)
{
//-----------------------
//-----SETUP UART 1------
//-----------------------
//At bootup, we need pin 16 to be set to UART1_RTS
//pin 17 to be set to UART1_CTS
//pin 18 to be set to UART1_TXD
//pin 19 to be set to UART1_RXD

//OPEN THE UART
//Flags defined in fcntl.h
//	O_RDONLY - Open for reading only
//	O_RDWR - Open for reading and writing
//	O_WRONLY - Open for writing only
//	O_NDELAY - returns failure status of reading (look into)
//printf("HELP ME IM LOST");
int uart1_filestream = open("/dev/ttyS4", O_RDONLY | O_NOCTTY | O_NDELAY);
//int uart1_filestream = 1;
if (uart1_filestream == -1)
{
//ERROR cannot open serial port
printf("Error - Unable to open UART. Ensure it is not in use by another application\n");
}
//printf("HELLO: %i",uart1_filestream);
//std::cout << "HELP ME IM LOST" << std::endl;
//printf("HELLO: %i",uart1_filestream);
//usleep(1000000);

//Configure the UART
// The flags are defined in /usr/include/termios.h
struct termios options;
tcgetattr(uart1_filestream, &options);
options.c_cflag = B19200 | CS8 | PARENB | CLOCAL | CREAD;
options.c_iflag = IGNPAR;
options.c_oflag = 0;
options.c_lflag = 0;
tcflush(uart1_filestream, TCIFLUSH);
tcsetattr(uart1_filestream, TCSANOW, &options);

short tx_data[8] = {0x01,0x03,0x00,0x08,0x00,0x07,0x085,0xCA};
write(uart1_filestream,&tx_data,8*sizeof(short));


//----CHECK FOR ANY RX BYTES ----
if (uart1_filestream != -1)
{
//Read up to 255 characters
	unsigned char rx_buffer[256];
	int rx_length = read(uart1_filestream, (void*)rx_buffer, 255);
	printf("RX_Length: %i", rx_length);
	std::cout << "HELP ME IM LOST" << std::endl;
	usleep(1000000);
	while(rx_length < 255)
	{
		if (rx_length < 0)
		{
		usleep(1000000);
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
		std::cout << "HELP ME IM LOST" << std::endl;
		usleep(1000000);
		}
	}

}

close(uart1_filestream);
}
