#ifndef COMM_H
#define COMM_H

#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

namespace STOUT
{
  class serial_comm
  {
  public:
    int set_arduino_comm();
    int set_ADS_comm();
    int set_UART_comm();
  private:

  };
}

#endif
