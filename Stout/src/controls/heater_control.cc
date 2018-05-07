#include "heater_control.h"

namespace STOUT {
  // GPIO 346 and 351 are used for heater control
  void heater_control::heater_eval(int T1, int T2)
  {
    // Max temp for heater to be turned on
    int heater_Tmax = 5;  // deg C
    if (T1 > heater_Tmax)
    {
      system("echo 0 > /sys/class/gpio/gpio346/value");
    }
    else
    {
      system("echo 1 > /sys/class/gpio/gpio346/value");
      //printf("Heater 1 On\n");
    }
    if (T2 > heater_Tmax)
    {
      system("echo 0 > /sys/class/gpio/gpio351/value");
    }
    else
    {
      system("echo 1 > /sys/class/gpio/gpio351/value");
      //printf("Heater 2 On\n");
    }
  }
}
