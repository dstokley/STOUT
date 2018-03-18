#include "heater_control.h"

namespace STOUT {
  // GPIO 346 and 351 are used for heater control
  void heater_eval(int T1, int T2)
  {
    if (T1 > heater_Tmax)
    {
      system("echo 0 > /sys/class/gpio/gpio344/value");
    }
    else
    {
      system("echo 1 > /sys/class/gpio/gpio344/value");
    }
    if (T2 > heater_Tmax)
    {
      system("echo 0 > /sys/class/gpio/gpio351/value");
    }
    else
    {
      system("echo 1 > /sys/class/gpio/gpio351/value");
    }
  }
}
