#ifndef EXECUTE_H
#define EXECUTE_H

#include "handler.h"
namespace STOUT
{
  class execute
  {

  public:

    // Loop for all STOUT actions
    int start_loop();

    // Functions used for interrupts and main loop
    static gboolean GPIO_event(GIOChannel *channel, GIOCondition condition, gpointer user_data);
    static gboolean timeout_event(gpointer user_data);
    static gboolean ext_main(gpointer user_data);

  private:

  };
}

#endif
