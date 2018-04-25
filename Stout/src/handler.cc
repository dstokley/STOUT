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
     write(fd,data,26);

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

  void handler::write_to_flash(char const* file, char* ts, char* sd, float* ad)
  {
      // STORE THE EMCS DATA -----------------------------------------------------
      char* EMCS_file;
      strcat(EMCS_file, file);
      strcat(EMCS_file,"EMCS_Date/EMCS_Date.txt");
      FILE *f1 = fopen(EMCS_file, "a");
      if (f1==NULL)
      {
        printf("Error opening EMCS file!\n");
        exit(1);
        throw SystemHaltException();
      }
      else
      {
        fprintf(f1,"%s\t%i\t%i\t%i\t%i\t%i\t%i\t%i\t%li\t%i\t%i\t%i\t%i\n",ts, sd[0] | sd[1] << 8,sd[2] | sd[3] << 8,sd[4] | sd[5] << 8,sd[6] | sd[7] << 8,
        sd[8] | sd[9] << 8,sd[10] | sd[11] << 8,sd[12] | sd[13] << 8,(long)(sd[14] | sd[15] << 8 | sd[16] << 16 | sd[17] << 24),
        sd[18] | sd[19] << 8,sd[20] | sd[21] << 8,sd[22] | sd[23] << 8,sd[24] | sd[25] << 8);
        fclose(f1);
      }

      // STORE THE ADS DATA ------------------------------------------------------
      char* ADS_file;
      strcat(ADS_file, file);
      strcat(ADS_file,"ADS_Data/ADS_Data.txt");
      FILE *f2 = fopen(ADS_file, "a");
      if (f2==NULL)
      {
        printf("Error opening ADS file!\n");
        exit(1);
        throw SystemHaltException();
      }
      else
      {
        for(int i = 0; i < 10; i++)
        {
          fprintf(f2,"%s\t%f\t%f\t%f\t%f\t%x\n",ad[i*5],ad[i*5+1],ad[i*5+2],ad[i*5+3],ad[i*5+4]);
        }
        fclose(f2);
      }
    }

  void write_spectrum(char const* file, char* ts, std::array<float, 2048> spect)
  {
    char* spec_file;
    strcat(spec_file, file);
    strcat(spec_file, ts);
    strcat(spec_file, ".txt");

    FILE *f = fopen(spec_file,"w");
    if(f==NULL)
    {
      printf("Error opening SPECTROMETER file!\n");
      exit(1);
      throw SystemHaltException();
    }
    else
    {
      for(int i = 0; i < sizeof(spect); i++)
      {
        fprintf(f,"%f ", spect[i]);
      }
      fprintf(f, "\n");
      fclose(f);
    }
  }
}
