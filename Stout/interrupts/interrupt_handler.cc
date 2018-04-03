// Script for setting up and handling interrrupts in the Linux OS. There are
// three interrupts. Two are based on GPIO pins which are for signaling the
// UV spectrometer to begin taking data and for receiving humidity data from
// the Arduino. The thrid interrupts is based on a real-time clock (RTC) driver.

// Set timer interrupt to high priority
#define G_PRIORITY_DEFAULT  -10

// Required libraries
#include <stdio.h>
#include <signal.h>
#include <glib.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <fcntl.h>

// Function declarations
static gboolean GPIO_event(GIOChannel *channel, GIOCondition condition, gpointer user_data);
static gboolean timeout_event(gpointer user_data);
static gboolean ext_main(gpointer user_data);

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
}

static gboolean GPIO_event(GIOChannel *channel, GIOCondition condition, gpointer user_data)
{
  // Signal event call and setup variables
  std::cerr << "GPIO_event" << std::endl;
  GError *error = 0;
  gsize bytes_read = 0;
  gchar buf[1];

  // Read value from GPIO file and print to standard error
  g_io_channel_seek_position(channel, 0, G_SEEK_SET, 0);
  GIOStatus rc = g_io_channel_read_chars(channel, buf, 1, &bytes_read, &error);
  std::cerr << "data:" << buf << std::endl;

  return 1;
}

static gboolean timeout_event(gpointer user_data)
{
  // Indicate a timer event has occured
  std::cerr << "timeout_event" << std::endl;
  return 1;
}

static gboolean ext_main(gpointer user_data)
{
  // Processes that occur when no interrupts are present
  std::cerr << "idle state" << std::endl;
  return 1;
}
