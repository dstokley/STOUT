#include <stdio.h>
#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <WinTypes.h>
#include <ftd2xx.h>
#include <sys/time.h>

int main(int argv, char* argc[])
{
  FT_STATUS ftStatus;
  FT_HANDLE ftHandle;

  FT_SetVIDPID(0x0403, 0xFAF0);
  //the following is per the user manual for thor device.
  ftStatus = FT_Open(0, &ftHandle);
  // Set baud rate to 115200.
  const int uBaudRate=115200;
  ftStatus =  FT_SetBaudRate(ftHandle, (ULONG)uBaudRate);

  // 8 data bits, 1 stop bit, no parity
  ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
  // Pre purge dwell 50ms.
  usleep(5000);
  // Purge the device.
  ftStatus = FT_Purge(ftHandle, FT_PURGE_RX | FT_PURGE_TX);
  // Post purge dwell 50ms.
  usleep(5000);
  ftStatus = FT_ResetDevice(ftHandle);
  // Set flow control to RTS/CTS.
  ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_RTS_CTS, 0, 0);
  // Set RTS.
  ftStatus = FT_SetRts(ftHandle);

  //lets flash the led, MGMSG_MOD_IDENTIFY
  BYTE buf[6] ={0x23,0x2,0,0,0x21,0x1};
  // d = 0x21, s = 0x01
  DWORD written = 0;
  /*******************/
  ftStatus = FT_Write(ftHandle, buf, (DWORD)6, &written);//4= FT_IO_ERROR
  /*******************/

  usleep(5000);

  BYTE buf_reldist[12] = {0x45,0x04,0x06,0x00,0xA1,0x01,0x01,0x00,0x40,0x0D,0x33,0x00};
  written = 0;
  ftStatus = FT_Write(ftHandle, buf_reldist, (DWORD)12, &written);

  usleep(5000);

  BYTE buf_relmove[6] = {0x48,0x04,0x01,0x00,0x21,0x01};
  written = 0;
  ftStatus = FT_Write(ftHandle, buf_relmove, (DWORD)6, &written);



}
