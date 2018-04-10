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

    struct termios tty;
    memset (&tty, 0, sizeof tty);
    if (tcgetattr (portname, &tty) != 0)
    {
      return -1;
    }

    cfsetospeed(&tty, 115200);
    cfsetispeed(&tty, 115200);

    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    tty.c_iflag &= ~IGNBRK;         // ignore break signal
    tty.c_lflag = 0;                // no signaling chars, no echo,
                                    // no canonical processing
    tty.c_oflag = 0;                // no remapping, no delays
    tty.c_cc[VMIN]  = 0;            // read doesn't block
    tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                    // enable reading
    tty.c_cflag &= ~(PARENB | PARODD);      // shut off 0
    tty.c_cflag |= 0;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CRTSCTS;

    if (tcsetattr (portname, TCSANOW, &tty) != 0)
    {
      return -1;
    }

    memset (&tty, 0, sizeof tty);
    if (tcgetattr (portname, &tty) != 0)
    {
      return -1;
    }

    tty.c_cc[VMIN]  = 0 ? 1 : 0;
    tty.c_cc[VTIME] = 5;            	// 0.5 seconds read timeout

    if (tcsetattr (portname, TCSANOW, &tty) != 0)
    {
      return -1;
    }

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
    struct termios options;
    tcgetattr(fd, &options);
    tcsetattr(fd,TCSANOW,&options);
    //system("stty -F /dev/ttyUSB0 -hupcl ignbrk ignpar -icrnl -ixon -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke 19200");

    return fd;
  }

  // This function is only used for transmitting data during testing
  int serial_comm::set_UART_comm()
  {
    const char* UART_portname = "/dev/ttyAMA0";  // Arduino location

    // Setup serial communication with Arduino
    int portname = open (UART_portname, O_RDWR | O_NOCTTY | O_SYNC);
    if (portname < 0)
    {
      return -1;
    }

     struct termios options;
    tcgetattr(portname, &options);
    tcsetattr(portname,TCSANOW,&options);
    system("stty -F /dev/ttyAMA0 -hupcl ignbrk ignpar -icrnl -ixon -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke 115200");

    //struct termios tty;
    // memset (&tty, 0, sizeof tty);
    //if (tcgetattr (portname, &tty) != 0)
    //{
    //  return -1;
    //}

    //cfsetospeed(&tty, 115200);
    //cfsetispeed(&tty, 115200);

    //tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    //tty.c_iflag &= ~IGNBRK;         // ignore break signal
    //tty.c_lflag = 0;                // no signaling chars, no echo,
                                    // no canonical processing
    //tty.c_oflag = 0;                // no remapping, no delays
    //tty.c_cc[VMIN]  = 0;            // read doesn't block
    //tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

    //tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

    //tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                    // enable reading
    //tty.c_cflag &= ~(PARENB | PARODD);      // shut off 0
    //tty.c_cflag |= 0;
    //tty.c_cflag &= ~CSTOPB;
    //tty.c_cflag &= ~CRTSCTS;

    //if (tcsetattr (portname, TCSANOW, &tty) != 0)
    //{
    //  return -1;
    //}

    //memset (&tty, 0, sizeof tty);
    //if (tcgetattr (portname, &tty) != 0)
    //{
    //  return -1;
    //}

    //tty.c_cc[VMIN]  = 0 ? 1 : 0;
    //tty.c_cc[VTIME] = 5;            	// 0.5 seconds read timeout

    //if (tcsetattr (portname, TCSANOW, &tty) != 0)
    //{
    //  return -1;
    //}

    return portname;
  }

}
