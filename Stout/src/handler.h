#ifndef HANDLER_H
#define HANDLER_H

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
//#include <glib.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>
#include "serial_comm.h"
#include "sensors/spectrometer/spectrometer.h"
#include "sensors/camera/camera.h"
#include "controls/optics_control.h"
#include "controls/heater_control.h"
#include "sensors/ADS/ADS_read.h"
//#include "systemhaltexception.h"

namespace STOUT
{
  class handler
  {
  public:
    char* receive_arduino_data();
    void UART_transmit(unsigned char* data);
    void save_ADS_data(float * angles, signed char add_info);

    //void read_sensor_data();
    //void call_to_write();

    // struct data_frame
    // {
    //   clock_t time_stamp;
    //   std::array<float,Spectrometer::kNumPixels> spectrum;
    //   float spectrometer_temp_UV;
    //   float spectrometer_temp_vis;
    //   float UDOO_temp;
    //   float storage_temp;
    //   float motor_hor_temp;
    //   float motor_vert_temp;
    //   float power_temp;
    //   float ext_front_temp;
    //   float ext_back_temp;
    //   float humidity;
    //   float pressure;
    //   float GPS;
    //   std::array<float,10> azimuth_angles;
    //   std::array<float,10> elevation_angles;
    // };

    //data_frame get_frame_data();
  
  private:
    // Sensor objects
    // Spectrometer spectrometer;
    // Camera camera;
    // ADS ADS;
    //serial_comm Comm_obj;
    //ADS ADS_obj;
    //Spectrometer Spec_obj;
    //heater_control Heater_obj;

    // Storage data objects for regular data
    // These are kept open for performance
    //std::ofstream slc_data_file{"/mnt/slcdrive/datafile",std::ios::binary|std::ios::app};
    //std::ofstream mlc_data_file{"/mnt/64GB_MLC/datafile",std::ios::binary|std::ios::app};
    //
    // // Data storage objects here
    //
    //void write_to_flash(std::ofstream& file);
    //
    //template <class T> std::ostream& binarywrite(std::ostream& stream, const T& value);
    //
    //data_frame frame_data;
    //
    //const float max_heater_temp = 15; // deg C
    // const float min_heater_temp = 5;  // deg C
    };

}

#endif
