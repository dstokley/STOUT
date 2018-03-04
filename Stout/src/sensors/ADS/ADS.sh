#!/bin/bash
stty -F /dev/ttyS4 19200 raw -echo
exec 3</dev/ttyS4
  cat <&3 > /tmp/ttyDump.dat &
  PID=$!
    echo -e "\x01\x03\x00\x08\x00\x07\x85\xCA" > /dev/ttyS4
    sleep 0.2s
  kill $PID
exec 3<&-
cat /tmp/ttyDump.dat
