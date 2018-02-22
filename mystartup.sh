#!/bin/bash
# Put it in /etc/init.d
### BEGIN INIT INFO
# Provides:          mystartup.sh
# Required-Start:    $remote_fs $syslog
# Required-Stop:     $remote_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Example initscript
# Description:       This file should be used to construct scripts to be
#                    placed in /etc/init.d.  This example start a
#                    single forking daemon capable of writing a pid
#                    file.  To get other behavoirs, implemend
#                    do_start(), do_stop() or other functions to
#                    override the defaults in /lib/init/init-d-script.
### END INIT INFO

cd /sys/class/gpio

echo 346 > export

cd gpio346

echo out > direction
echo 1 > value

cd ..

echo 351 > export

cd gpio351

echo out > direction
echo 1 > value

cd ..

echo 344 > export

cd gpio344

echo out > direction
echo 1 > value

cd ..

echo 349 > export

cd gpio349

echo out > direction
echo 1 > value

cd ..

echo 347 > export

cd gpio347

echo out > direction
echo 1 > value

cd ..

echo 408 > export

cd gpio408

echo in > direction

cd ..

echo 350 > export

cd gpio350

echo in > direction

cd ..

echo 366 > export

cd gpio366

echo in > direction
