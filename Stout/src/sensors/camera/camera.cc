#include "camera.h"

namespace STOUT
{
  void Camera::take_picture()
  {
    system("cam_capture.sh");
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,sizeof(buffer),"%d-%m-%Y %I:%M:%S",timeinfo);
    std::string str(buffer);

    system( ("cp picture.jpg /mnt/mlcdrive/images/" + str + ".jpg").c_str());

  }
}
