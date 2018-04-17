#include "optics_control.h"

#define PI 3.141592653

namespace STOUT
{

// Deterimine desired scan location on Sun
// float* optics_control::optics_determine(char location)
// {
//
// }

// Calculate required actuations from x and y angles
float* optics_control::optics_compute(float x, float y)
{
  // Optical dimensions
  const double O1_offset[3] = {16.15,-9.28,45.78};
  double r_cg[3] = {0.0,0.0,0.0};
  double r_vg[3] = {41.45,-107.68,-45.09};
  double r_hg[3] = {-2.14,-52.68,-46.16};
  double r_vb[3] = {49.3,-65.72,-45.09};
  double r_hb[3] = {36.79,-53.21,-45.09};
  double d_ap = 100.6602;

  // Variable declarations
  double r_ap0[3];
  double r_ap_vb0[3];
  double r_ap_hb0[3];
  double temp_vec[3] = {0,0,d_ap};
  double r_ap[3];
  int i;

  for (i=0; i<3; i++)
  {
    r_cg[i] = r_cg[i] - O1_offset[i];
    r_vg[i] = r_vg[i] - O1_offset[i];
    r_hg[i] = r_hg[i] - O1_offset[i];
    r_vg[i] = r_vb[i] - O1_offset[i];
    r_hb[i] = r_hb[i] - O1_offset[i];
  }

  // Calculate vectors from apex of ball joint centers at 0 deg pointing deflection
  for (i=0; i<3; i++)
  {
    r_ap0[i] = r_cg[i] - temp_vec[i];
  }

  for (i=0; i<3; i++)
  {
    r_ap_vb0[i] = r_vb[i] - r_ap0[i];
    r_ap_hb0[i] = r_hb[i] - r_ap0[i];
  }

  // Convert x and y from degrees to radians
  x = x*PI/180;
  y = y*PI/180;

  // Find position of actuated apex
  r_ap[0] = d_ap*(-sin(y)*cos(x));
  r_ap[1] = d_ap*(sin(x));
  r_ap[2] = d_ap*(-cos(y)*cos(x));

  // Convert r_ap_vb and r_ap_hb to cage gimbal frame
  // Rotation matrix
  double rot_mat[3][3];
  rot_mat[0][0] = cos(y);
  rot_mat[0][1] = sin(y)*sin(x);
  rot_mat[0][2] = sin(y)*sin(x);
  rot_mat[1][0] = 0;
  rot_mat[1][1] = cos(x);
  rot_mat[1][2] = -sin(y);
  rot_mat[2][0] = -sin(y);
  rot_mat[2][1] = cos(y)*sin(x);
  rot_mat[2][2] = cos(x)*cos(y);

  // Setting up matrix-vector multiplications
  double r_ap_vb[3];
  double r_ap_hb[3];
  cblas_dgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,3,1,3,1.0,*rot_mat,3,r_ap_vb0,3,0.0,r_ap_vb,3);
  cblas_dgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,3,1,3,1.0,*rot_mat,3,r_ap_hb0,3,0.0,r_ap_hb,3);

  // Find ball joint locations
  double r_cg_vb[3];
  double r_cg_hb[3];

  for (i=0; i<3; i++)
  {
    r_cg_vb[i] = r_ap_vb[i] + r_ap[i] + O1_offset[i];
    r_cg_hb[i] = r_ap_hb[i] + r_ap[i] + O1_offset[i];
  }

  // Calculate actuation lengths
  double temp_vec1[3], temp_vec2[3];
  double Lh, Lv;
  float L1, L2;

  for (i=0; i<3; i++)
  {
    // Temporary vectors for calculations
    temp_vec1[i] = r_cg_vb[i] - r_vg[i] - O1_offset[i];
    temp_vec2[i] = r_cg_hb[i] - r_hg[i] - O1_offset[i];
  }

  // Horizontal distance from motor gimbal center to ball joint center
  Lh = sqrt(pow(temp_vec1[0],2) + pow(temp_vec1[1],2) + pow(temp_vec1[2],2));
  // Vertical distance from motor gimbal center to ball joint center
  Lv = sqrt(pow(temp_vec2[0],2) + pow(temp_vec2[1],2) + pow(temp_vec2[2],2));

  // Calculate actual actuations based on dimensions
  L1 = (float)(Lh + 0);        // Need to add necessary additions/subtractions
  L2 = (float)(Lv + 0);

  // Place actuation distances in output array
  float* lengths =(float*) malloc(sizeof(float)*2);
  lengths[0] = L1;
  lengths[1] = L2;

  return lengths;
}

void optics_control::optics_transmit(float* lengths)
{
  // Communication object creation, opening arduino port
  serial_comm optics_comm;
  int fd = optics_comm.set_arduino_comm();

  // Placing actuations into variables
  float L1, L2;
  L1 = (float)*(lengths + 0);
  L2 = (float)*(lengths + 1);

  // Send actuation data to Arduino via serial
  write(fd, &L1, 4);
  usleep(500);
  write(fd, &L2, 4);
  usleep(500);

  // Close port
  close(fd);

}


void optics_control::polarizer_rotate(char home)
{
  // Handle, status, and writing variables
  FT_STATUS ftStatus;   // May want to check this value for error handling
  FT_HANDLE ftHandle;
  DWORD written = 0;

  // Disable uneeded mods
  system("rmmod ftdi_sio");
  system("rmmod usbserial");

  // Locate device through its VID and PID numbers
  FT_SetVIDPID(0x0403, 0xFAF0);

  // Open device and set baud/message size
  ftStatus = FT_Open(0, &ftHandle);
  assert(ftStatus == FT_OK);

  // Set baud rate to 115200.
  const long uBaudRate = 115200;
  ftStatus =  FT_SetBaudRate(ftHandle, (ULONG)uBaudRate);
  assert(ftStatus == FT_OK);

  // 8 data bits, 1 stop bit, no parity
  ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);
  assert(ftStatus == FT_OK);

  // Pre purge dwell 0.5 ms.
  usleep(500);

  // Purge the device.
  ftStatus = FT_Purge(ftHandle, FT_PURGE_RX | FT_PURGE_TX);
  assert(ftStatus == FT_OK);

  // Post purge dwell 0.5 ms.
  usleep(500);

  ftStatus = FT_ResetDevice(ftHandle);
  assert(ftStatus == FT_OK);

  // Set flow control to RTS/CTS.
  ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_RTS_CTS, 0, 0);
  assert(ftStatus == FT_OK);

  // Set RTS.
  ftStatus = FT_SetRts(ftHandle);
  assert(ftStatus == FT_OK);

  // Check if we need to rotate polarizer back to 0 degrees or forward 22.5 deg
  if (home == 0)
  {
    // Set desired relative rotation amount in degrees (22.5)
    BYTE buf_reldist[12] = {0x45,0x04,0x06,0x00,0xA1,0x01,0x01,0x00,0x00,0xE0,0x2E,0x00};
    written = 0;
    ftStatus = FT_Write(ftHandle, buf_reldist, (DWORD)12, &written);
    assert(ftStatus == FT_OK);

    usleep(500);

    // Move the desired relative rotation amount (22.5 degrees)
    BYTE buf_relmove[6] = {0x48,0x04,0x01,0x00,0x21,0x01};
    written = 0;
    ftStatus = FT_Write(ftHandle, buf_relmove, (DWORD)6, &written);
    assert(ftStatus == FT_OK);

  }
  else if (home == 1)
  {
    // Set home parameters
    BYTE buf_homeparam[12] = {0x50,0x04,0x06,0x00,0xA1,0x01,0x01,0x00,0x00,0x00,0x00,0x00};
    written = 0;
    ftStatus = FT_Write(ftHandle, buf_homeparam, (DWORD)12, &written);
    assert(ftStatus == FT_OK);

    usleep(500);

    // Rotate back to home
    BYTE buf_home[6] = {0x53,0x04,0x01,0x00,0x21,0x01};
    written = 0;
    ftStatus = FT_Write(ftHandle, buf_home, (DWORD)6, &written);
    assert(ftStatus == FT_OK);
  }

  // Close the port
  ftStatus = FT_Close(ftHandle);
  assert(ftStatus == FT_OK);

}
}
