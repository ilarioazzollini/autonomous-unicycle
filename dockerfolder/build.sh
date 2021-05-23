#!/bin/bash

THIS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

UID=`id -u`
GID=`id -g`

IMAGE_NAME=ubuntu_nav_$USER

docker build \
    --build-arg uid="$UID" \
    --build-arg gid="$GID" \
    -t $IMAGE_NAME \
    $THIS_DIR
