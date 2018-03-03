#include "controls/optics_control.h"
#include "sensors/ADS/ADS_read.h"

namespace STOUT
{
  class execute
  {

  public:

    // Loop for all STOUT actions
    void start_loop();
    // Assign an object to the optics_control class
    optics_control optics;
    ADS ADS_obj;

  private:
    // Communication configuration with Arduino
    char const *portname = "/dev/ttyACM0";
    int baud = 115200;


  };


}
