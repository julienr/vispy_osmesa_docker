#!/bin/bash
set -e # exit on non-zero return code
export DEBIAN_FRONTEND=noninteractive
apt-get update
apt-get upgrade -y
