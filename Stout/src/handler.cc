#include "handler.h"

namespace STOUT
{
  char* handler::receive_arduino_data()
  {
    serial_comm arduino_comm;
    int fd = arduino_comm.set_arduino_comm();

    int bufsize = 26;
    char* buffer = (char*)malloc(sizeof(char) * bufsize);

    read(fd, buffer, sizeof(char)*20); 	// Read all 20 characters
    //printf("Number of bytes received = %i\n",n);
    usleep(3000);
  	// if (n > 0) {
  	// 	int i;
  	// 	for (i = 0; i < n; i++) {
  	// 		printf("%x\n",buffer[i]);
  	// 	}
  	// }
    long raw_temp = 0;
    int udoo_temp;
    char tmp[256] = {0x00};

    FILE* fp = popen("cat /sys/devices/virtual/thermal/thermal_zone0/temp", "r");

    while(fgets(tmp,4095,fp)!=NULL)
    {
      raw_temp += atol(tmp);
    }

    udoo_temp = (int)(raw_temp/1000);
    //printf("UDOO temp = %i\n",udoo_temp);

    buffer[20] = udoo_temp&0xFF;
    buffer[21] = (udoo_temp>>8)&0xFF;

    // for (int i=0;i<21;i++)
    // {
    //   printf("Byte %i = %c\n",i,buffer[i]);
    // }

    close(fd);

    return buffer;
  }

  void handler::UART_transmit(char* data)
  {
    // Open USB line
    serial_comm UART_comm;
    int fd = UART_comm.set_UART_comm();

     // Trasmit data over UART
     //int bytes_written = 0;
     //write(fd,data,26);
     write(fd,data,22);

     // Delay for appropriate amount of time
     usleep(3000);
     //printf("%i Bytes Transmitted \n", bytes_written);

    //  // Receive data over USB
    //  unsigned char read_buffer[4];
    //  int bytes_read = 0;
    //  bytes_read = read(fd,&read_buffer,4);
    //  printf("%i Bytes Received \n",bytes_read);
    //
    // int i;
    // for (i=0;i<4;i++)
    // {
    //   //printf("Byte %i = %x\n",i,read_buffer[i]);
    //   printf("Byte %i = %x\n",i,read_buffer[i]);
    // }

    close(fd);
  }

    void handler::save_EMCS_data(char* EMCS_data)
  {
    //const char* save_point = "/mnt/64GB_MLC/datafile"; // Save location (USB)
    FILE *f = fopen("TVAC_Data.txt", "a");
    if (f == NULL)
    {
      printf("Error opening file!\n");
      exit(1);
    }

  /* print some text */
  //const char *text = "Write this to the file";
  //fprintf(f, "Some text: %s\n", text);

  time_t rawtime;
  struct tm * timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  // time_t now = time(0);
  //printf("%s",asctime(timeinfo));

  fprintf(f,"%i\t%i\t%i\t%i\t%i\t%i\t%i\t%li\t%i\t%i\t%i\t%i\t%s",EMCS_data[0] | EMCS_data[1] << 8,EMCS_data[2] | EMCS_data[3] << 8,EMCS_data[4] | EMCS_data[5] << 8,EMCS_data[6] | EMCS_data[7] << 8,
  EMCS_data[8] | EMCS_data[9] << 8,EMCS_data[10] | EMCS_data[11] << 8,EMCS_data[12] | EMCS_data[13] << 8,(long)(EMCS_data[14] | EMCS_data[15] << 8 | EMCS_data[16] << 16 | EMCS_data[17] << 24),
  EMCS_data[18] | EMCS_data[19] << 8,EMCS_data[20] | EMCS_data[21] << 8,EMCS_data[22] | EMCS_data[23] << 8,EMCS_data[24] | EMCS_data[25] << 8,asctime(timeinfo));


  fclose(f);
  }

  void handler::save_ADS_data(float* angles, signed char add_info)
  {
    //const char* save_point = "/mnt/64GB_MLC/datafile"; // Save location (USB)
    FILE *f = fopen("ADS_data.txt", "a");
    if (f == NULL)
    {
      printf("Error opening file!\n");
      exit(1);
    }

  /* print some text */
  //const char *text = "Write this to the file";
  //fprintf(f, "Some text: %s\n", text);

  time_t rawtime;
  struct tm * timeinfo;
  time(&rawtime);
  timeinfo = localtime(&rawtime);
  // time_t now = time(0);
 printf("%s",asctime(timeinfo));

 fprintf(f,"%f\t%f\t%f\t%f\t%x\t%s",angles[0],angles[1],angles[2],angles[3],add_info,asctime(timeinfo));


fclose(f);
  }

//   void handler::read_sensor_data()
//   {
//     // Read timestamp measurement
//     // This timestamp represents seconds since Unix epoch
//     std::chrono::seconds ms = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch());
//     frame_data.time_stamp = ms.count();
//     std::cout << "Timestamp: " << frame_data.time_stamp << std::endl;
//
//     // Read main instrument(spectrometer)
//     // If the spectrometer cannot be read from, throw an exception to restart the system
//     if (!spectrometer.ReadSpectrum(frame_data.spectrum)) {
//       throw SystemHaltException();
//     }
//
//     // Take a picture, if necessary
//     // The time stamp is necessary to know how long ago a picture was taken
//     camera.take_picture();
//
//     // Read temperature sensors
//     // These sensors are used for heater control. Overheating is a concern, so
//     // if the sensors are not responding, assume sensor is already at desired temperature
//
//
// // START WORKING HERE!
//     if (!spectrometer.ReadSpectrometerTemperature(frame_data.spectrometer_temp_UV)) {
//       frame_data.spectrometer_temp_UV = max_heater_temp;
//     }
//
//     if (!spectrometer.ReadSpectrometerTemperature(frame_data.spectrometer_temp_vis)) {
//       frame_data.spectrometer_temp_vis = max_heater_temp;
//     }
//
//     if (!spectrometer.ReadSpectrometerTemperature(frame_data.spectrometer_temp_UV)) {
//       frame_data.spectrometer_temp_UV = max_heater_temp;
//     }
//
//     if (!spectrometer.ReadSpectrometerTemperature(frame_data.motor_vert_temp)) {
//       frame_data.motor_vert_temp = max_heater_temp;
//     }
//
//
//     // Read environmental sensors
//     // These sensors are not used in heating calculations so return 0 if they cannot be read
//     if (!upper_battery_temperature_sensor_.ReadTemperature(frame_data.upper_battery_temperature)) {
//       frame_data.upper_battery_temperature = execute::GetMaxHeaterTemp();
//     }
//
//     if (!lower_battery_temperature_sensor_.ReadTemperature(frame_data.lower_battery_temperature)) {
//       frame_data.lower_battery_temperature = execute::GetMaxHeaterTemp();
//     }
//
//     if (!storage_temperature_sensor_.ReadTemperature(frame_data.storage_temperature)) {
//       frame_data.storage_temperature = execute::GetMaxHeaterTemp();
//     }
//
//     if (!rpi_temperature_sensor_.ReadTemperature(frame_data.rpi_temperature)) {
//       frame_data.rpi_temperature = execute::GetMaxHeaterTemp();
//     }
//
//     if (!external_temperature_sensor_.ReadTemperature(frame_data.external_temperature)) {
//       frame_data.external_temperature = 0;
//     }
//
//     if (!humidity_sensor_.ReadHumidity(frame_data.humidity)) {
//       frame_data.humidity = 0;
//     }
//
//     for(int i = 0; i < 4; ++i){
//     	frame_data.attitude_values[i] = radiance_ads.ads_read(i+1);
//     }
//
//   }
//
//   // Writes the frame data to a csv file
//   void handler::call_to_write()
//   {
//     // Make sure at least one data file can be written to
//     // If not, restart the system
//     if (!slc_data_file.good() && !mlc1_data_file.good()) {
//       //throw SystemHaltException();
//     }
//
//     // Writes the data(measurements) to all three drives every second
//     write_to_flash(slc_data_file);
//     write_to_flash(mlc1_data_file);
//   }
//
//   void handler::write_to_flash(std::ofstream& file)
//   {
//     // Check that the data file is OK
//     // If not OK, do nothing
//     if (file.good()) {
//
//       // Write timestamp of measurement
//       handler::binarywrite(file,frame_data.time_stamp);
//
//       // Write the spectrometer measurements
//       // for (auto& i : frame_data.spectrum) {
//       //   handler::binarywrite(file,i);
//       // }
//       // Write the engineering/housekeeping measurements to the given file
//       handler::binarywrite(file,frame_data.spectrometer_temp_UV);
//       handler::binarywrite(file,frame_data.spectrometer_temp_vis);
//       handler::binarywrite(file,frame_data.UDOO_temp);
//       handler::binarywrite(file,frame_data.storage_temp);
//       handler::binarywrite(file,frame_data.motor_temp);
//       handler::binarywrite(file,frame_data.camera_temp);
//       handler::binarywrite(file,frame_data.power_temp);
//       handler::binarywrite(file,frame_data.ext_front_temp);
//       handler::binarywrite(file,frame_data.ext_back_temp);
//       handler::binarywrite(file,frame_data.humidity);
//       handler::binarywrite(file,frame_data.pressure);
//       handler::binarywrite(file,frame_data.GPS);
//
//       // Write the attitude measurements
//       for (auto& i : frame_data.azimuth_angles) {
//         handler::binarywrite(file,i);
//       }
//
//       for (auto& i : frame_data.elevation_angles) {
//         handler::binarywrite(file,i);
//       }
//
//       file.flush();
//     }
//   }
//
//   // Gets the frame_data struct for other routines
//   handler::data_frame handler::get_frame_data() {return frame_data;}
//
//   // Takes a value and writes the binary information to given stream
//   template <class T> std::ostream& handler::binarywrite(std::ostream& stream, const T& value) {
//     return stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
//   }

}
