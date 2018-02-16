#include "optics_control.h"

// Calculate required actuations from x and y angles
distances optics_control::optics_compute(double x,double y)
{

  // Variable declarations
  double r_ap0[3];
  double r_ap_vb0[3];
  double r_ap_hb0[3];
  double temp_vec[3] = {0,0,d_ap};
  double r_ap[3];
  int i;

  // Output structure
  struct Distances distances;

  // Calculate vectors from apex of ball joint centers at 0 deg pointing deflection
  for (i=0; i<3; i++)
  {
    r_ap0[i] = r_cg[i] - temp_vec[i];
  }

  for (i=0; i<3; i++)
  {
    r_ap_vb0[i] = r_vb - r_ap0;
    r_ap_hb0[i] = r_hb - r_ap0;
  }

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
  cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,3,1,3,1.0,*rot_mat,3,r_ap_vb0,3,0.0,r_ap_vb,3);
  cblas_dgemm(CblasRowMajor,CblasNoTrans,CblasNoTrans,3,1,3,1.0,*rot_mat,3,r_ap_hb0,3,0.0,r_ap_hb,3);

  // Find ball joint locations
  double r_cg_vb[3];
  double r_cg_hb[3];

  for (i=0; i<3; i++)
  {
    r_cg_vb[i] = r_ap_vb[i] + r_ap[i] + O1_offset[i];
    r_cg_hb[i] = r_ap_hb[i] + r_ap[i] + O1_offset[i];
  }

  // Calculate actuation lengths
  double Lh, Lv, L1, L2;
  double temp_vec1[3], temp_vec2[3];

  for (i=0; i<3; i++)
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
  L1 = (Lh + 0);        // Need to add necessary additions/subtractions
  L2 = (Lv + 0);

  // Place in struture for output
  distances.Lh = L1;
  distances.Lv = L2;

  return distances;
}

void optics_control::optics_transmit(float L1, float L2)
{

}
