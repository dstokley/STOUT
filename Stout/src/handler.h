#ifndef HANDLER_H
#define HANDLER_H

// Set timer interrupt to high priority
#define G_PRIORITY_DEFAULT  -10

// Required libraries
#include </usr/include/glib-2.0/glib.h>
#include <stdio.h>
#include <sys/types.h>
#include <chrono>
#include <limits>
#include <thread>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <array>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>
#include <math.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include "serial_comm.h"
#include "sensors/spectrometer/spectrometer.h"
#include "sensors/camera/camera.h"
#include "controls/optics_control.h"
#include "controls/heater_control.h"
#include "sensors/ADS/ADS_read.h"
#include "systemhaltexception.h"

namespace STOUT
{
  class handler
  {
  public:
    char* receive_arduino_data();
    void UART_transmit(char* data);

    // void read_sensor_data();
    // void call_to_write();

    //data_frame get_frame_data();

    // Storage data objects for regular data
    // These are kept open for performance
    char const* slc_file = "/mnt/slcdrive/";
    char const* mlc_file = "/mnt/mlcdrive/";

    // Writes a data hanlder to appropriate files
    void write_to_flash(char const* file, char* ts, char* sd, float* ad);
    void write_spectrum(char const* file, char* ts, std::array<float, 2048> spectrum);

  private:
    // Sensor objects
    // Spectrometer spectrometer;
    // Camera camera;
    // ADS ADS;
    //serial_comm Comm_obj;
    //ADS ADS_obj;
    //Spectrometer Spec_obj;
    //heater_control Heater_obj;
    //void take_pic();

    //
    // // Data storage objects here
    //
    //
    // template <class T> std::ostream& binarywrite(std::ostream& stream, const T& value);
    //
    // data_frame frame_data;
    //
    // const float max_heater_temp = 15; // deg C
    // const float min_heater_temp = 5;  // deg C
    };

}

#endif
