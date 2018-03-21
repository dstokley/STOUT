#include "execute.h"
#include <iostream>

using namespace std;

int main()
{
  // Creat object and start the system loop
  STOUT::execute UDOO;
  UDOO.start_loop();
}
