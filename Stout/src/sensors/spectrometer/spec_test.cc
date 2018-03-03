#include "spectrometer.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <array>

  int main(void)
  {

    Spectrometer spec;
    float temp;

    spec.ReadSpectrometerTemperature(temp);
    printf("Spectrometer Temp = %f \n", temp);

    return 1;
}
