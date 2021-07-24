#!/bin/bash

THIS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

UID=`id -u`
GID=`id -g`

IMAGE_NAME=autonomous_unicycle_ros2_$USER

docker build \
    --build-arg uid="$UID" \
    --build-arg gid="$GID" \
    -f $THIS_DIR/Dockerfile_ros2 \
    -t $IMAGE_NAME \
    $THIS_DIR
