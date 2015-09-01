#!/bin/bash
set -e # exit on non-zero return code
export DEBIAN_FRONTEND=noninteractive
apt-get install -y build-essential \
                   pkg-config \
                   libtool \
                   automake \
                   git \
                   clang \
                   llvm-dev \
                   llvm-3.3-dev \
                   wget

# Download OSMesa sources and GLU
wget ftp://ftp.freedesktop.org/pub/mesa/11.0.0/mesa-11.0.0-rc1.tar.gz -P /root
wget ftp://ftp.freedesktop.org/pub/mesa/glu/glu-9.0.0.tar.gz -P /root
