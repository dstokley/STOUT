#include "avaspec/avaspec.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

int main()
{
  if (AVS_Init(0)==ERR_SUCCESS) {
      printf("WE F'D");
      //throw std::runtime_error("Could not initialize spectrometer");
    }
  printf("WE MADE IT");


}
