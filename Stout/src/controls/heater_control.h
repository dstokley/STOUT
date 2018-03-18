#ifndef HEATER_H
#define HEATER_H

#include <stdio.h>
#include <stdlib.h>

namespace STOUT{
    class heater_control{
    public:
      void heater_eval(int T1, int T2);
    private:
      // Max temp for heater to be turned on
      int heater_Tmax = 5;  // deg C
    };
}
#endif
