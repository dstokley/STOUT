#define G_PRIORITY_DEFAULT  -10
#include "execute.h"

// Required global variables
char scan_loc = 0, pol_loc = 0, spec_init = 0;

namespace STOUT
{

  int execute::start_loop()
  {
    // Setup save locations for all data

    // EMCS sensors and heaters
    // FILE *f = fopen("TVAC_Data.txt", "a");
    // if (f == NULL)
    //   {
    // printf("Error opening file!\n");
    // exit(1);
    //   }
    // fprintf(f,"\nInt Temp 1\tInt Temp 2\tInt Temp 3\tInt Temp 4\tInt Temp 5\tExt Temp 1\tExt Temp 2\tPressure\tHumidity\tUDOO Temo\tSpec Temp\tADS Temp\tTime\n");
    //
    // fclose(f);

    // Spectrometers

    // ADS angles and motor actuations


    // Set up main loop
    GMainLoop* loop = g_main_loop_new(0, 0);

    // Set up GPIO interrupt based on any change of value (for spectrometer reading)
    int fd = open("/sys/class/gpio/gpio349/value", O_RDONLY | O_NONBLOCK);
    GIOChannel* channel = g_io_channel_unix_new(fd);
    GIOCondition cond = GIOCondition(G_IO_PRI);
    guint id1 = g_io_add_watch(channel, cond, GPIO_event, 0);

    // Set up 100 ms timer interrupt (for ADS data)
    guint id2 = g_timeout_add(100, timeout_event, loop);

    // Set up idle source function (main loop)
    GSource* source = g_idle_source_new();
    guint id3 = g_source_attach(source, 0);
    g_source_set_callback(source, ext_main, 0, NULL);

    // Begin main loop
    g_main_loop_run(loop);

    // Unreference main loop
    g_main_loop_unref(loop);

    return 0;
  }

    static gboolean ext_main(gpointer user_data)
    {
      // Processes that occur when no interrupts are present
      //std::cerr << "idle state" << std::endl;

      // Setup required objects
      handler handler_obj;
      heater_control heater_obj;
      ADS ADS_obj;

      // Initialize all necessary variables for data collection
      float* ADS_data;
      char* sensor_data;
      float temp_float;
      int time_counter = 0;

      while(1)
      {

      // Read the spectrometer themistor voltage and convert to temperature
      bool status = spec_obj.ReadSpectrometerTemperature(temp_float);
      if (status != true)
      {
        continue;
      }

      // Round spectrometer temperature to nearest degree
      int spec_temp = (int)round(temp_float);
      // printf("Temp Spec = %i\n",spec_temp);

      // Read the ADS data
      ADS_data = ADS_obj.ADS_read();

      // Grab ADS temperature value from data
      float temp0 = ADS_data[0];
      int ADS_temp = (int)round(temp0);
      // printf("ADS Temp = %i\n",ADS_temp);

      // Receive data from the Arduino via serial
      sensor_data = handler_obj.receive_arduino_data();

      // Isolate heater control temperature
      int T1; // Will want to replace T1 with 2nd spectrometer temperature
      T1 = sensor_data[0] | sensor_data[1] << 8;

      // Turn heaters on/off based on temperatures of spectrometers
      heater_obj.heater_eval(spec_temp, T1);

      // Add spectrometer and ADS temperatures to data array
      sensor_data[22] = (char)((spec_temp)&0xFF);
      sensor_data[23] = (char)(((spec_temp>>8)&0xFF));
      sensor_data[24] = (char)((ADS_temp)&0xFF);
      sensor_data[25] = (char)(((ADS_temp>>8)&0xFF));

      // Save data to USB drive
      handler_obj.save_EMCS_data(sensor_data);

      // Free dynamically allocated variable memory
      free(ADS_data);
      free(sensor_data);

      }

      return 1;
    }

    static gboolean GPIO_event(GIOChannel *channel, GIOCondition condition, gpointer user_data)
    {
      // Setup spectrometer object
      Spectrometer spec_obj;
      optics_control optics_obj;

      // Signal event call and setup variables
      //std::cerr << "GPIO_event" << std::endl;
      GError *error = 0;
      gsize bytes_read = 0;
      gchar buf[1];

      // Read value from GPIO file
      g_io_channel_seek_position(channel, 0, G_SEEK_SET, 0);
      GIOStatus rc = g_io_channel_read_chars(channel, buf, 1, &bytes_read, &error);
      //std::cerr << "data:" << buf << std::endl;

      // Check if spectrometer is already reading spectrum
      if(spec_init == 1)
      {
        // Don't start a new exposure if already exposing
        return 1;
      }
      else
      {
        spec_init = 1;
      }

      // Start spectrometer spectrum read
      std::array<float,2048>& f_spectrum;
      bool status = spec_obj.ReadSpectrum(f_spectrum);

      if (status == true)
      {
        // Save spectrum data to USB drive
        spec_init = 0;
      }

      // Variable to check if next scan location should be selected
      char next_loc = 0;

      // Rotate polarizer to correct posisiton
      if(pol_loc < 7)
      {
        // Rotate polarizer to next increment of 22.5 degrees
        pol_loc++;
        optics_obj.polarizer_rotate(0);
      }
      else
      {
        // Rotate polarizer to home posistion
        pol_loc = 0;
        optics_obj.polarizer_rotate(1);
        next_loc = 1;
      }

      // Update scan location (if necessary)
      if (next_loc == 1)
      {
        // Update scan location for optics control
        scan_loc++;
        // Reset scan location to 0 when all scans have been made
      }


      return 1;
    }

    static gboolean timeout_event(gpointer user_data)
    {
      // Setup ADS and optics objects
      ADS ADS_obj;
      optics_control optics_obj;

      // Initialize all necessary variables for data collection
      float x = 0, y = 0;
      float* ADS_data;
      float* lengths;

      // Read the ADS data
      ADS_data = ADS_obj.ADS_read();

      // Grab ADS temperature value from data
      float temp0 = ADS_data[0];
      int ADS_temp = (int)round(temp0);
      // printf("ADS Temp = %i\n",ADS_temp);

      // Grab filtered angle values from data
      x = ADS_data[1];
      y = ADS_data[2];

      // Compute required actuation distances
      lengths = optics_obj.optics_compute(x,y);

      // Print angles to screen
      //printf("X Angle = %f deg\nY Angle = %f deg\n",x,y);

      // Trasmit required actuation distances to the Arduino via serial line
      optics_obj.optics_transmit(lengths);

      // Save ADS and actuation data to USB drive

      // Free dynamically allocated variable memory
      free(ADS_data);
      free(lengths);

      // Indicate a timer event has occured
      //std::cerr << "timeout_event" << std::endl;

      return 1;
    }

}
