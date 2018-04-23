#!/bin/bash

# TITLE: Camera Capture Function
# AUTHOR: Zack Allen
# EDITED: 2/8/18

# INPUTS: First argument to function is filename ($1)

fswebcam -r 1920x1080 --jpeg 95 -F 1 picture.jpg
