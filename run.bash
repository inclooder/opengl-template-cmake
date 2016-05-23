#!/bin/bash

# Dirty workaround for glibc issue https://bugs.launchpad.net/ubuntu/+source/nvidia-graphics-drivers-319/+bug/1248642
export LD_PRELOAD=/lib/x86_64-linux-gnu/libpthread.so.0 
./opengl-template


