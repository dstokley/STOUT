#include <unistd.h>
#include </usr/include/x86_64-linux-gnu/sys/reboot.h>
#include "systemhaltexception.h"
namespace STOUT {

  const char* SystemHaltException::what() const throw(){
    SystemHaltException::RestartSystem();
    return "";
  }
  // Error handler function; first syncs the file system and then restarts the pi
  void SystemHaltException::RestartSystem() {
    sync();
    reboot(RB_AUTOBOOT);

  }

}
