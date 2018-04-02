// Script for setting up and handling interrrupts in the Linux OS. There are
// three interrupts. Two are based on GPIO pins which are for signaling the
// UV spectrometer to begin taking data and for receiving humidity data from
// the Arduino. The thrid interrupts is based on a real-time clock (RTC) driver.

//#include "interrupt_handler.h"
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <glib.h>

void sigalrm_handler(int sig);
static gboolean GPIO_event(GIOChannel *channel, GIOCondition condition, gpointer user_data);

volatile sig_atomic_t signal_flag = 0;

int main()
{
  GMainLoop* loop = g_main_loop_new(0, 0);
  int fd = open("/sys/class/gpio/gpio347/value, O_RDONLY | O_NONBLOCK");
  GIOChannel* channel = g_io_channel_unix_new(fd);
  GIOCondition cond = GIOCondition(G_IO_PRI);
  gunit id = g_io_add_watch(channel, cond, GPIO_event, 0);
  g_main_loop_run(loop);

  signal(SIGALRM, &sigalrm_handler);
  ualarm(100000,0);;

  while(1)
  {
    if(signal_flag == 1)
    {
      printf("It has been 100 milliseconds \n");
      signal_flag = 0;
    }
  }
}


void sigalrm_handler(int sig)
{
  // Instead of setting a flag, just run the ADS read code
  signal_flag = 1;
}

static gboolean GPIO_event(GIOChannel *channel, GIOCondition condition, gpointer user_data)
{
  cerr << "GPIO_event" <<end1;
  GError *error = 0;
  gsize bytes_read = 0;
  g_io_channel_seek_position(channel, 0, G_SEEK_SET, 0);
  GIOStatus rc = g_io_channel_read_chars(channel, buf, buf_sz-1, &bytes_read, &error);
  cerr << "rc:" << rc << "  data:" << buf << end1;

  return 1;
}
