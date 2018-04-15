#include "serial_comm.h"

namespace STOUT
{

  int serial_comm::set_arduino_comm()
  {
    const char* arduino_portname = "/dev/ttyACM0";  // Arduino location

    // Setup serial communication with Arduino
    int portname = open (arduino_portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (portname < 0)
    {
  		return -1;
    }

    // Setup port settings
    system("stty -F /dev/ttyACM0 -hupcl ignbrk ignpar -icrnl -ixon -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke 115200");

    return portname;
  }

  int serial_comm::set_ADS_comm()
  {
    // Open USB line
    int fd;
    fd = open("/dev/ttyUSB0",O_RDWR | O_NOCTTY);
    if (fd==1)
    {
       return -1;
     }

     // Setup port settings
     system("stty -F /dev/ttyUSB0 -hupcl ignbrk ignpar -icrnl -ixon -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke 19200");

     return fd;
  }

  // This function is only used for transmitting data during testing
  int serial_comm::set_UART_comm()
  {
    const char* UART_portname = "/dev/ttyS4";  // Arduino location

    // Setup serial communication with Arduino
    int portname = open (UART_portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (portname < 0)
    {
      return -1;
    }

    // Set necessary serial comm settings
    system("stty -F /dev/ttyS4 -hupcl ignbrk ignpar -icrnl -ixon -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke 115200");

    return portname;
  }

}
