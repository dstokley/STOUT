#ifndef EXECUTE_H
#define EXECUTE_H

//#include "handler.h"
# include "sensors/spectrometer/spectrometer.h"
namespace STOUT
{
  class execute
  {

  public:

    // Loop for all STOUT actions
    int start_loop();

  private:
    // Assign objects to classes
    // optics_control optics_obj;
    // handler handler_obj;
    // serial_comm comm_obj;
    // ADS ADS_obj;
    Spectrometer Spec_obj;

  };
}

#endif
