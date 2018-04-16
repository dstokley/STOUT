#include "execute.h"
#include <iostream>


using namespace std;

int main()
{

  // Set up main loop
  GMainLoop* loop = g_main_loop_new(0, 0);

  // Set up GPIO interrupt based on any change of value
  int fd = open("/sys/class/gpio/gpio349/value", O_RDONLY | O_NONBLOCK);
  GIOChannel* channel = g_io_channel_unix_new(fd);
  GIOCondition cond = GIOCondition(G_IO_PRI);
  guint id1 = g_io_add_watch(channel, cond, GPIO_event, 0);

  // Set up 100 ms timer interrupt
  guint id2 = g_timeout_add(100, timeout_event, loop);

  // Set up idle source function (main loop)
  GSource* source = g_idle_source_new();
  guint id3 = g_source_attach(source, 0);
  g_source_set_callback(source, ext_main, 0, NULL);
  //guint id4 = g_idle_add(ext_main, 0);

  // Begin main loop
  g_main_loop_run(loop);

  // Unreference main loop
  g_main_loop_unref(loop);

  return 0;


  // Creat object and start the system loop
  STOUT::execute UDOO;
  UDOO.start_loop();
}
