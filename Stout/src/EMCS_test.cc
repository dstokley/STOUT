#include "controls/heater_control.h"
#include "sensors/internal_temp/internal_temp.h"
#include <unistd.h>
#include <fstream>
#include <string>
#include <iostream>
#include "math.h"

using namespace std;

int main()
{
  // Initialize all variables
  int temps[10800][4];
  int timestamp[10800];
  int count;
  int prev_temp = 0;
  count = 0;

  // These used for time and auto implies automatic detection
  auto end;
  std::chrono::duration<double> wait_time;

  // Initialize time
  auto start = std::chrono::system_clock::now();

  // Begin data collection
  while(true)
  {
    // Read and store temp and timestamp
    temps[count][0] = (int)Read_Temperature();
    temps[count][1] = (int)Read_Temperature();
    temps[count][2] = (int)Read_Temperature();
    temps[count][3] = (int)Read_Temperature();
    timestamp[count] = count;

    // If steady state has been reached break while loop
    if(count != 0 && (abs(temps[count]-temp[count-1]) < .01)){
      break;
    }

    // Perform heater control
    // Need to choose the two temperatures to determine heaters
    // or use a linear combination of the temperatures
    // heater_eval(T1, T2)

    // Increase counter
    count = count + 1;

    // Determine and wait time for 1 second frequency
    end = std::chrono::system_clock::now();
    wait_time = (1 - (start-end))*10^6;
    usleep(wait_time);

    // Set start to the current time for next loop
    start = std::chrono::system_clock::now();
  }

  // Write results to a text file
  ofstream results;
  results.open("results.txt",ios::app|ios::ate);
  results << "\t\t\t\t\t\t" << timestamp << "," << temps << "\n";

  // Set pointer to the end of the file
  results.seekp(0,std::ios::end);
}
