# Dockerfile for an OSMesa-enabled Ubuntu 14.04 with vispy

FROM ubuntu:14.04
MAINTAINER Julien Rebetez "julien.rebetez@gmail.com"

ADD src/_setup /tmp
RUN chmod +x /tmp/*.sh
RUN /tmp/0_upgrade.sh
RUN /tmp/1_build_deps.sh
RUN /tmp/2_build_osmesa.sh
ADD src/c_example /root/c_example
RUN /tmp/3_test_osmesa.sh
RUN /tmp/4_python_deps.sh
