// Platform header
#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#  include <windows.h>
#else
#  include <unistd.h>
#endif

// Include FieldTalk package header
// #include "MbusAsciiMasterProtocol.hpp"
#include "MbusRtuMasterProtocol.hpp"


/*****************************************************************************
 * Gobal data
 *****************************************************************************/

const char *portName = "/dev/ttyS4";
int readByteSent[8];
int writeByteSent[8];

//MbusAsciiMasterProtocol mbusProtocol; // Use this declaration for ASCII
MbusRtuMasterProtocol mbusProtocol; // Use this declaration for RTU


/*****************************************************************************
 * Function implementation
 *****************************************************************************/

void openProtocol()
{
   int result;

   result = mbusProtocol.openProtocol(portName,
                                      19200L, // Baudrate
                                      8,      // Databits
                                      1,      // Stopbits
                                      0);     // Even parity
   if (result != FTALK_SUCCESS)
   {
      fprintf(stderr, "Error opening protocol: %s!\n",
              getBusProtocolErrorText(result));
      exit(EXIT_FAILURE);
   }
}


void closeProtocol()
{
   mbusProtocol.closeProtocol();
}


void runPollLoop()
{
   char dataArr[19];

   for (;;)
   {
      int i;
      int result;

      result = mbusProtocol.readMultipleRegisters(1, 100,
                                                  dataArr,
                                                  sizeof(dataArr));
      if (result == FTALK_SUCCESS)
         for (i = 0; i < int(sizeof(dataArr) / 2); i++)
            printf("[%d]: %hd\n", 100 + i, dataArr[i]);
      else
      {
         fprintf(stderr, "%s!\n", getBusProtocolErrorText(result));
         // Stop for fatal errors
         if (!(result & FTALK_BUS_PROTOCOL_ERROR_CLASS))
            return;
      }

#ifdef _WIN32
      Sleep(1000);
#else
      sleep(1);
#endif
   }
}




#if defined(_WIN32_WCE)
int wmain()
#else
int main()
#endif
{
   int master_addr = 0;
   int slave_addr = 1;
   int write_start_reg = 1;
   int read_start_reg = 9;
   int read_end_erg = 16;
   writeByteSent = [1,3,0,8,0,7,133,202];


   openProtocol();
   mbusProtocol.writeMultipleRegisters(slave_addr,write_start_reg,writeByteSent,8);
   sleep(1);
   mbusProtocol.readMultipleRegisters(slave_addr,read_start_reg,readByteSent,8);
   printf("Additional info = %x\n",readByteSent);
   closeProtocol();
   return (EXIT_SUCCESS);
}
