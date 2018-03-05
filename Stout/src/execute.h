#ifndef EXECUTE_H
#define EXECUTE_H

#include "controls/optics_control.h"
//#include "sensors/ADS/ADS_read.h"
#include "handler.h"

namespace STOUT
{
  class execute
  {

  public:

    // Loop for all STOUT actions
    int start_loop();

  private:
    // Assign objects to classes
    optics_control optics_obj;
    handler handler_obj;
    serial_comm comm_obj;

  };
}

#endif
