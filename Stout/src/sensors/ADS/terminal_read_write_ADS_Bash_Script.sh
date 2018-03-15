#!/bin/bash
stty -F /dev/ttyUSB0 -hupcl ignbrk ignpar -icrnl -ixon -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke 19200


echo -e "\x01\x03\x00\x08\x00\x07\x85\xCA und normaler Text" > /dev/ttySUSB0
#cat -v /dev/ttyS4
