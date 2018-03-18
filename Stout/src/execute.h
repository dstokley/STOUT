#ifndef EXECUTE_H
#define EXECUTE_H

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
    optics_control Optics_obj;
    handler Handler_obj;
    serial_comm Comm_obj;
    ADS ADS_obj;
    Spectrometer Spec_obj;
    heater_control Heater_obj;

  };
}

#endif
