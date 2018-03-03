#include "camera.h"

namespace STOUT
{
  void Camera::take_picture()
  {
    system("cam_capture.sh");
  }
}
