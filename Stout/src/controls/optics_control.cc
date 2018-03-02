#include "optics_control.h"
#include <iostream>

#define PI 3.141592653

// Calculate required actuations from x and y angles
double* optics_control::optics_compute(double x,double y)
{

  // Variable declarations
  double r_ap0[3];
  double r_ap_vb0[3];
  double r_ap_hb0[3];
  double temp_vec[3] = {0,0,d_ap};
  double r_ap[3];
  int i;

  // Calculate vectors from apex of ball joint centers at 0 deg pointing deflection
  for (i=0; i<2; i++)
  {
    r_ap0[i] = r_cg[i] - temp_vec[i];
  }

  for (i=0; i<2; i++)
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

  for (i=0; i<2; i++)
  {
    r_cg_vb[i] = r_ap_vb[i] + r_ap[i] + O1_offset[i];
    r_cg_hb[i] = r_ap_hb[i] + r_ap[i] + O1_offset[i];
  }

  // Calculate actuation lengths
  double Lh, Lv, L1, L2;
  double temp_vec1[3], temp_vec2[3];

  for (i=0; i<2; i++)
  {
    // Temporary vectors for calculations
    temp_vec1[i] = r_cg_vb[i] - r_vg[i] - O1_offset[i];
    temp_vec2[i] = r_cg_hb[i] - r_hg[i] - O1_offset[i];
  }

  // Horizontal distance from motor gimbal center to ball joint center
  Lh = sqrt(pow(temp_vec1[0],2) + pow(temp_vec1[1],2) + pow(temp_vec1[3],2));
  // Vertical distance from motor gimbal center to ball joint center
  Lv = sqrt(pow(temp_vec2[0],2) + pow(temp_vec2[1],2) + pow(temp_vec2[3],2));

  // Calculate actual actuations based on dimensions
  L1 = Lh + 0;        // Need to add necessary additions/subtractions
  L2 = Lv + 0;

  // Place actuation distances in output array
  double *Lengths =(double *) malloc(sizeof(double)*2);
  Lengths[0] = L1;
  Lengths[1] = L2;

  return Lengths;
}

void optics_control::optics_transmit(double* Lengths, int fd)
{
  // Placing actuations into variables
  float L1, L2;
  L1 = (float)*(Lengths + 0);
  L2 = (float)*(Lengths + 1);

  // Send actuation data to Arduino via serial
  write(fd,&L1,4);
  write(fd,&L2,4);

}

int optics_control::set_interface_attribs(int fd, int speed, int parity)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf ("error %d from tcgetattr", errno);
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // ignore break signal
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                printf ("error %d from tcsetattr", errno);
                return -1;
        }
        return 0;
}

void optics_control::set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                printf ("error %d from tggetattr", errno);
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
                printf ("error %d setting term attributes", errno);
}

void optics_control::polarizer_rotate(char location)
{
  // Handle, status, and writing variables
  FT_STATUS ftStatus;
  FT_HANDLE ftHandle;
  DWORD written = 0;

  // Locate device through its VID and PID numbers
  FT_SetVIDPID(0x0403, 0xFAF0);

  // Open device and set baud/message size
  ftStatus = FT_Open(0, &ftHandle);
  // Set baud rate to 115200.
  const int uBaudRate=115200;
  ftStatus =  FT_SetBaudRate(ftHandle, (ULONG)uBaudRate);
  // 8 data bits, 1 stop bit, no parity
  ftStatus = FT_SetDataCharacteristics(ftHandle, FT_BITS_8, FT_STOP_BITS_1, FT_PARITY_NONE);

  // Pre purge dwell 5ms.
  usleep(500);
  // Purge the device.
  ftStatus = FT_Purge(ftHandle, FT_PURGE_RX | FT_PURGE_TX);
  // Post purge dwell 5ms.
  usleep(500);
  ftStatus = FT_ResetDevice(ftHandle);

  // Set flow control to RTS/CTS.
  ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_RTS_CTS, 0, 0);
  // Set RTS.
  ftStatus = FT_SetRts(ftHandle);

  // Check if we need to rotate polarizer back to 0 degrees or forward 22.5 deg
  if (location != 0)
  {
    // Set desired relative rotation amount in degrees (22.5)
    BYTE buf_reldist[12] = {0x45,0x04,0x06,0x00,0xA1,0x01,0x01,0x00,0x00,0xE0,0x2E,0x00};
    written = 0;
    ftStatus = FT_Write(ftHandle, buf_reldist, (DWORD)12, &written);

    usleep(500);

    // Move the desired relative rotation amount (22.5 degrees)
    BYTE buf_relmove[6] = {0x48,0x04,0x01,0x00,0x21,0x01};
    written = 0;
    ftStatus = FT_Write(ftHandle, buf_relmove, (DWORD)6, &written);

  }
  else if (home == 1)
  {
    // Set home parameters
    BYTE buf_homeparam[12] = {0x50,0x04,0x06,0x00,0xA1,0x01,0x01,0x00,0x00,0x00,0x00,0x00};
    written = 0;
    ftStatus = FT_Write(ftHandle, buf_homeparam, (DWORD)12, &written);

    usleep(500);

    // Rotate back to home
    BYTE buf_home[6] = {0x53,0x04,0x01,0x00,0x21,0x01};
    written = 0;
    ftStatus = FT_Write(ftHandle, buf_home, (DWORD)6, &written);
  }
}
