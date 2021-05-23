#!/bin/bash

THIS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

XSOCK=/tmp/.X11-unix
XAUTH=/tmp/.docker.xauth
touch $XAUTH
xauth nlist $DISPLAY | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -

IMAGE_NAME=ubuntu_nav_$USER

docker run \
    -e DISPLAY=$DISPLAY \
    --volume=$XSOCK:$XSOCK:rw \
    --volume=$XAUTH:$XAUTH:rw \
    --volume=$THIS_DIR/..:/root/autonomous-unicycle \
    --env="XAUTHORITY=${XAUTH}" \
    --device=/dev/dri/card0:/dev/dri/card0 \
    -it $IMAGE_NAME bash
