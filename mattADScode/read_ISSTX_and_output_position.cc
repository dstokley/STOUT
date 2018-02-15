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
//At bootup, we need pin 16 to be set to UART2_RTS
//pin 17 to be set to UART1_CTS
//pin 18 to be set to UART1_TXD
//pin 19 to be set to UART1_RXD

//OPEN THE UART
//Flags defined in fcntl.h
//	O_RDONLY - Open for reading only
//	O_RDWR - Open for reading and writing
//	O_WRONLY - Open for writing only
//	O_NDELAY - returns failure status of reading (look into)	

uart1_filestream = open("/dev/ttys4", O_RDONLY | O_NOCTTY | O_NDELAY);
//int uart1_filestream = 1;
if (uart1_filestream == -1)
{
//ERROR cannot open serial port
printf("Error - Unable to open UART. Ensure it is not in use by another application\n");
}

//Configure the UART
// The flags are defined in /usr/include/termios.h
struct termios options;
tcgetattr(uart1_filestream, &options);
options.c_cflag = B9600 | CS8 | PARENB | CLOCAL | CREAD;
options.c_iflag = IGNPAR;
options.c_oflag = 0;
options.c_lflag = 0;
tcflush(uart1_filestream, TCIFLUSH);
tcsetattr(uart1_filestream, TCSANOW, &options);

//----CHECK FOR ANY RX BYTES ----
if (uart1_filestream != -1)
{
//Read up to 255 characters 
	unsigned char rx_buffer[256];
	int rx_length = read(uart1_filestream, (void*)rx_buffer, 255);	
	
	while(rx_length < 255)
	{
		if (rx_length < 0)
		{
		cout << "error" << endl;
		}
		else if (rx_length == 0)
		{
		cout << "no data waiting" << endl;
		}
		else
		{
		rx_buffer[rx_length] = '\0';
		printf("%i bytes read : %s\n",rx_length,rx_buffer);
		}
	}

}

close(uart1_filestream);
}
