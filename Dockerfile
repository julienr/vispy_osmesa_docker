# Dockerfile for an OSMesa-enabled Ubuntu 14.04 with vispy

FROM ubuntu:14.04
MAINTAINER Julien Rebetez "julien.rebetez@gmail.com"

ADD src/_setup /tmp
RUN chmod +x /tmp/*.sh
RUN /tmp/0_upgrade.sh
RUN /tmp/1_build_deps.sh
RUN /tmp/2_build_osmesa.sh
# Because python ctypes.util.find_library relies on running "gcc -l<libname>"
# to find libraries (acting as a linker), it ignores LD_LIBRARY_PATH
# But then, when loading the library, it uses ctypes.CDLL which uses
# LD_LIBRARY_PATH Basically, we need to setup both
ENV LIBRARY_PATH=/opt/osmesa_llvmpipe/lib:$LIBRARY_PATH
ENV LD_LIBRARY_PATH=/opt/osmesa_llvmpipe/lib:$LD_LIBRARY_PATH
ENV PYTHONPATH=/root/vispy:$PYTHONPATH
ADD src/c_example /root/c_example
RUN /tmp/3_test_osmesa.sh
RUN /tmp/4_python_deps.sh
