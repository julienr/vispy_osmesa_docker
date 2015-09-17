# Dockerfile for an OSMesa-enabled Ubuntu 14.04 with vispy

FROM ubuntu:14.04
MAINTAINER Julien Rebetez "julien.rebetez@gmail.com"

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update

RUN apt-get install -y build-essential \
                       pkg-config \
                       libtool \
                       automake \
                       git \
                       clang \
                       llvm-dev \
                       fontconfig \
                       llvm-3.3-dev \
                       wget

# Download OSMesa sources and GLU
RUN wget ftp://ftp.freedesktop.org/pub/mesa/11.0.0/mesa-11.0.0-rc1.tar.gz -P /root \
    && wget ftp://ftp.freedesktop.org/pub/mesa/glu/glu-9.0.0.tar.gz -P /root

ADD src/_setup/2_build_osmesa.sh /tmp/2_build_osmesa.sh
RUN /bin/bash /tmp/2_build_osmesa.sh

# Because python ctypes.util.find_library relies on running "gcc -l<libname>"
# to find libraries (acting as a linker), it ignores LD_LIBRARY_PATH
# But then, when loading the library, it uses ctypes.CDLL which uses
# LD_LIBRARY_PATH Basically, we need to setup both
ENV LIBRARY_PATH=/opt/osmesa_llvmpipe/lib:$LIBRARY_PATH
ENV LD_LIBRARY_PATH=/opt/osmesa_llvmpipe/lib:$LD_LIBRARY_PATH
ENV PYTHONPATH=/root/vispy:$PYTHONPATH
ADD src/c_example /root/c_example
ADD src/_setup/3_test_osmesa.sh /tmp/3_test_osmesa.sh
RUN /bin/bash /tmp/3_test_osmesa.sh

RUN apt-get install -y python-numpy \
                       python-setuptools \
                       python-dev \
                       python-fontconfig \
                       python-pytest \
                       python-pip \
                       python-nose \
                       python-nose2

RUN pip install pytest-cov flake8
