#!/bin/bash
# This runs a bash shell in a osmesa_vispy docker container
set -e

if [ ! -d vispy ]; then
    echo "This require vispy checkout in $PWD/'vispy'"
    echo "e.g. : git clone -b osmesa git@github.com:julienr/vispy.git"
    exit 1
fi

IMAGE_NAME="jrebetez/vispy_osmesa"

CMD="python examples/offscreen/simple_osmesa.py"

echo "Once in bash, you can execute the osmesa demo with :"
echo $CMD

sudo docker run -it --rm --name vispy_osmesa \
    -w /root/vispy \
    -v $PWD/vispy:/root/vispy $IMAGE_NAME \
    /bin/bash
