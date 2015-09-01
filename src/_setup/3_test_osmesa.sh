#!/bin/bash
# Test OSMesa by building and running a simple C example
set -e
cd /root/c_example
make
make run

# This should create a cube.bmp file
if [ ! -f /root/c_example/cube.bmp ]; then
    echo '/root/c_example/cube.bmp not created by c_example'
    exit 1 # error
fi
