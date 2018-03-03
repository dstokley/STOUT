#define LINUX_REBOOT_CMD_RESTART 0x4321fedc
#include <exception>


namespace STOUT {
  class SystemHaltException: public std::exception {
  public:

    virtual const char* what() const throw();
    static void RestartSystem();
  };

}
