#!/bin/bash
set -e # exit on non-zero return code
export DEBIAN_FRONTEND=noninteractive
apt-get install -y python-numpy \
                   python-setuptools \
                   python-fontconfig
