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
#include <string.h>

int main(int argv, char* argc[])
{
  //system("sudo rmmod ftdi_sio usbserial");

  FT_STATUS ftStatus;
  FT_HANDLE ftHandle;

  FT_SetVIDPID(0x0403, 0x6001);
  //the following is per the user manual for thor device.
  ftStatus = FT_Open(0, &ftHandle);
  // Set baud rate to 115200.
  const int uBaudRate=19200;
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
  ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0, 0);
  // Set RTS.
  ftStatus = FT_SetRts(ftHandle);

  // //lets flash the led, MGMSG_MOD_IDENTIFY
  // BYTE buf[6] ={0x23,0x2,0,0,0x21,0x1};
  // // d = 0x21, s = 0x01
  // /*******************/
  // ftStatus = FT_Write(ftHandle, buf, (DWORD)6, &n_n_written);//4= FT_IO_ERROR
  // /*******************/
  //
  // usleep(5000);

  // Read location from the encoder

  DWORD n_written = 0;
  DWORD n_read = 0;

  // Set desired relative rotation amount in degrees (22.5)
  BYTE buf_reldist[8] = {0x01,0x03,0x00,0x08,0x00,0x07,0x85,0xCA};
  n_written = 0;
  ftStatus = FT_Write(ftHandle, buf_reldist, (DWORD)8, &n_written);

  // if (n_written>0)
  // {
  //   printf("Bytes sent: %c\n", n_written);
  // }
  // else
  // {
  //   printf("No bytes sent\n");
  // }

  usleep(5000);

  DWORD RxBytes;
  DWORD TxBytes;
  DWORD EventDWord;
  BYTE buf_rc[19];


  FT_GetStatus(ftHandle,&RxBytes,&TxBytes,&EventDWord);
  if (RxBytes > 0) {
  ftStatus = FT_Read(ftHandle, buf_rc, (DWORD)19, &n_read);
  if (ftStatus == FT_OK) {
  // FT_Read OK
  }
  else {
  // FT_Read Failed
  }
  }



  usleep(5000);

  // if (n_read>0)
  // {
  //   printf("Bytes received: %c", n_read);
  // }
  // else
  // {
  //   printf("No bytes received\n");
  // }

  FT_Close(ftHandle);
}
