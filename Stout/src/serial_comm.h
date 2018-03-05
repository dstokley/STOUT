#ifndef COMM_H
#define COMM_H

#include <termios.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

namespace STOUT
{
  class serial_comm
  {
  public:
    int set_interface_attribs(int fd, int speed, int parity);
    void set_blocking(int fd, int should_block);
  private:

  };
}

#endif
