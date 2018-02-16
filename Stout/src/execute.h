#include "controls/optics_control.h"

namespace STOUT
{
  class execute
  {

  public:

    // Loop for all STOUT actions
    void start_loop();
    // Assign an object to the optics_control class
    optics_control optics;

    // Communication configuration with Arduino
    char const *portname = "/dev/ttyS0";
    int baud = 115200;

  };


}
