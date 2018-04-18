#include "execute.h"
#include </usr/include/glib-2.0/glib.h>

namespace STOUT
{
  // Script for setting up and handling interrrupts in the Linux OS. There are
  // three interrupts. Two are based on GPIO pins which are for signaling the
  // UV spectrometer to begin taking data and for receiving humidity data from
  // the Arduino. The thrid interrupts is based on a real-time clock (RTC) driver.



  int main()
  {
    // Set up main loop
    GMainLoop* loop = g_main_loop_new(0, 0);

    // Set up GPIO interrupt based on any change of value
    int fd = open("/sys/class/gpio/gpio349/value", O_RDONLY | O_NONBLOCK);
    GIOChannel* channel = g_io_channel_unix_new(fd);
    GIOCondition cond = GIOCondition(G_IO_PRI);
    guint id1 = g_io_add_watch(channel, cond, GPIO_event, 0);

    // Set up 100 ms timer interrupt
    guint id2 = g_timeout_add(100, timeout_event, loop);

    // Set up idle source function (main loop)
    GSource* source = g_idle_source_new();
    guint id3 = g_source_attach(source, 0);
    g_source_set_callback(source, ext_main, 0, NULL);
    //guint id4 = g_idle_add(ext_main, 0);

    // Begin main loop
    g_main_loop_run(loop);

    // Unreference main loop
    g_main_loop_unref(loop);

    return 0;
  }

  static gboolean GPIO_event(GIOChannel *channel, GIOCondition condition, gpointer user_data)
  {
    // Signal event call and setup variables
    std::cerr << "GPIO_event" << std::endl;
    GError *error = 0;
    gsize bytes_read = 0;
    gchar buf[1];

    // Read value from GPIO file and print to standard error
    g_io_channel_seek_position(channel, 0, G_SEEK_SET, 0);
    GIOStatus rc = g_io_channel_read_chars(channel, buf, 1, &bytes_read, &error);
    //std::cerr << "data:" << buf << std::endl;

    if (!spec_obj.ReadSpectrum(data_frame.spectrum)) {
    //       throw SystemHaltException();
        ;
    }

    return 1;
  }

  static gboolean timeout_event(gpointer user_data)
  {
    // Indicate a timer event has occured
    std::cerr << "timeout_event" << std::endl;

    ADS_data = ADS_obj.ADS_read();

    //SEND BYTES TO ADS
    //wait
    //RECIEVE BYTES ADS
    return 1;
  }

  static gboolean ext_main(gpointer user_data)
  {
    handler handler_obj;
    heater_control heater_obj;
    ADS ADS_obj;
    Spectrometer spec_obj;
    //optics_control optics_obj;

    // Initialize the spectrometer
    //spec_obj.Spectrometer();

    // GPS in range flag
    // Define by altitude lost at: 10 km
    GPS_flag = 1

    milliseconds ms_start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()));
    milliseconds ms_end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()));
    milliseconds ms_diff = 0;
    first_flag = 1;
    while(true)
    {
      if(first_flag && ms_diff < std::chrono::milliseconds(1000))
      {
        ms_start = system_clock::now().time_since_epoch();

        //float x = 0, y = 0;
        //float* Lengths;
        float* ADS_data;
        char* sensor_data;
        float temp_float;

        // Read the spectrometer themistor voltage
        bool status = spec_obj.ReadSpectrometerTemperature(temp_float);
        int spec_temp = (int)round(temp_float);
        //printf("Temp Spec = %i\n",spec_temp);

        // Read the ADS data
        ADS_data = ADS_obj.ADS_read();
        // Grab ADS temperature value from data
        float temp0 = ADS_data[0];
        int ADS_temp = (int)round(temp0);
        //printf("ADS Temp = %i\n",ADS_temp);

        // Compute required actuation distances
        //Lengths = Optics_obj.optics_compute(x,y);

        // Trasmit required actuation distances to the Arduino via Serial
        //Optics_obj.optics_transmit(Lengths, fd);

        // Receive data from the Arduino via serial
        // IF IN GPS RANGE GRAB IT
        if(GPS_flag)
        {
          sensor_data = handler_obj.receive_arduino_data();
        }
        else
        {
          sensor_data = handler_obj.receive_arduino_data_no_gps();
        }


        // Isolate heater control temperature
        int T1;
        T1 = sensor_data[0] | sensor_data[1] << 8;
        //printf("Temp 1 = %i\n",T1);
        //printf("Byte 0 = %x\n",sensor_data[0]);

        // Turn heaters on/off based on temperatures
        heater_obj.heater_eval(spec_temp, T1);

        // Add spectrometer and ADS temperatures to data array
        sensor_data[22] = (char)((spec_temp)&0xFF);
        sensor_data[23] = (char)(((spec_temp>>8)&0xFF));
        sensor_data[24] = (char)((ADS_temp)&0xFF);
        sensor_data[25] = (char)(((ADS_temp>>8)&0xFF));
        //printf("Sensor data size: %lu\n",sizeof(sensor_data));
        // for(int i=0;i<25;i++)
        // {
        //   printf("%x\n",sensor_data[i]);
        // }
        // printf("\n\n");

        // TAKE CAMERA IMAGE
        handler_obj.take_pic();

        // Find time to read all data


        // Build Frame to save for USB
        handler_obj.sensor_datas = sensor_data;

        // Send EMCS data to external arduino via UART (for TVAC testing)
        // handler_obj.UART_transmit(sensor_data);

        // Free dynamically allocated variable memory
        //free(ADS_data);
        //free(Lengths);
        free(sensor_data);
        first_flag = 0;
      }
      else
      {
        if(ms_diff < std::chrono::milliseconds(1000))
        {
          ms_end = system_clock::now().time_since_epoch();
          ms_diff = ms_end - ms_start;
        }
        else
        {
          handler_obj.timestamp = ms_end;

          // Build Frame to save for USB
          handler_obj.ADS_datas = ADS_data;

          // Save data to USB drive
          handler_obj.WriteFrameToStorage();

          free(ADS_data);
        }
      }

    }

    return 1;
  }


  // auto *execute::readSpect()
  // {
  //   std::array<float,kNumPixels>& f_spectrum;
  //
  //   if (!spec_obj.ReadSpectrum(data_frame.spectrum)) {
  //   //       throw SystemHaltException();
  //       ;
  //   }
  //
  //   pthread_exit(NULL);
  // }


  int execute::start_loop()
  {
    //serial_comm comm_obj;
    handler handler_obj;
    heater_control heater_obj;
    ADS ADS_obj;
    Spectrometer spec_obj;
    //optics_control optics_obj;

    // Initialize the spectrometer
    //spec_obj.Spectrometer();

    // GPS in range flag
    // Define by altitude lost at: 10 km
    GPS_flag = 1

    milliseconds ms_start = duration_cast<milliseconds>(system_clock::now().time_since_epoch()));
    milliseconds ms_end = duration_cast<milliseconds>(system_clock::now().time_since_epoch()));
    milliseconds ms_diff = 0;


    // System loop
    while(true)
    {
      ms_start = system_clock::now().time_since_epoch();

      //float x = 0, y = 0;
      //float* Lengths;
      float* ADS_data;
      char* sensor_data;
      float temp_float;

      // Read the spectrometer themistor voltage
      bool status = spec_obj.ReadSpectrometerTemperature(temp_float);
      int spec_temp = (int)round(temp_float);
      //printf("Temp Spec = %i\n",spec_temp);

      // Read the ADS data
      ADS_data = ADS_obj.ADS_read();
      // Grab ADS temperature value from data
      float temp0 = ADS_data[0];
      int ADS_temp = (int)round(temp0);
      //printf("ADS Temp = %i\n",ADS_temp);

      // Compute required actuation distances
      //Lengths = Optics_obj.optics_compute(x,y);

      // Trasmit required actuation distances to the Arduino via Serial
      //Optics_obj.optics_transmit(Lengths, fd);

      // Receive data from the Arduino via serial
      // IF IN GPS RANGE GRAB IT
      if(GPS_flag)
      {
        sensor_data = handler_obj.receive_arduino_data();
      }
      else
      {
        sensor_data = handler_obj.receive_arduino_data_no_gps();
      }


      // Isolate heater control temperature
      int T1;
      T1 = sensor_data[0] | sensor_data[1] << 8;
      //printf("Temp 1 = %i\n",T1);
      //printf("Byte 0 = %x\n",sensor_data[0]);

      // Turn heaters on/off based on temperatures
      heater_obj.heater_eval(spec_temp, T1);

      // Add spectrometer and ADS temperatures to data array
      sensor_data[22] = (char)((spec_temp)&0xFF);
      sensor_data[23] = (char)(((spec_temp>>8)&0xFF));
      sensor_data[24] = (char)((ADS_temp)&0xFF);
      sensor_data[25] = (char)(((ADS_temp>>8)&0xFF));
      //printf("Sensor data size: %lu\n",sizeof(sensor_data));
      // for(int i=0;i<25;i++)
      // {
      //   printf("%x\n",sensor_data[i]);
      // }
      // printf("\n\n");

      // TAKE CAMERA IMAGE
      handler_obj.take_pic();

      // Find time to read all data
      ms_end = system_clock::now().time_since_epoch();
      ms_diff = ms_end - ms_start;

      // Sleep for remaining 1 second
      if(ms_diff < std::chrono::milliseconds(1000)){
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)-ms);
      }

      // Build Frame to save for USB
      handler_obj.timestamp = ms_end;
      handler_obj.sensor_datas = sensor_data;
      handler_obj.ADS_datas = ADS_data;

      // Save data to USB drive
      handler_obj.WriteFrameToStorage();

      // Send EMCS data to external arduino via UART (for TVAC testing)
      // handler_obj.UART_transmit(sensor_data);

      // Free dynamically allocated variable memory
      //free(ADS_data);
      //free(Lengths);
      free(sensor_data);
      free(ADS_data);

      sleep(1); // Sleep for 1 second (only for TVAC testing)
    }
  }
}
