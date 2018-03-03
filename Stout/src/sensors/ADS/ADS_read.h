#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

class ADS
{

public:
  // Function for reading data (azimuth and elevation angles) from ADS sensor
  void ADS_read();

private:
  // Communication parameters (UART)
  int baud = 19200;   // Default sensor baud rate
  const char* portname = "/dev/ttyS4";  // UART1 location
};
