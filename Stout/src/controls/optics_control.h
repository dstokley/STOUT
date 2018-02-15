#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>
#include <iostream>
#include <cblas.h>
#include <termios.h>
#include <string.h>
#include <errno.h>

// Class for entire optics control system

class optics_control
{

public:

  // Actuation computation function
  double* optics_compute(double x, double y);

  // Data transmission functions
  void optics_transmit(double* Lengths, int fd);
  int set_interface_attribs (int fd, int speed, int parity);
  void set_blocking (int fd, int should_block);

  // Polarizer control function
  void polarizer_rotate(int step);


private:

  // Optical dimensions (Need to include O1offset subtractions)
  const double O1_offset[3] = {16.15,-9.28,45.78};
  const double r_cg[3] = {0.0,0.0,0.0};
  const double r_vg[3] = {25.3,-116.96,-45.09};
  const double r_hg[3] = {-2.14,-52.68,-46.16};
  const double r_vb[3] = {49.3,-65.72,-45.09};
  const double r_hb[3] = {36.79,-53.21,-45.09};
  const double d_ap = 90.865;

};