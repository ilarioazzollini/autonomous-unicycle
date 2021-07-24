#!/bin/bash

THIS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

docker build -f Dockerfile_base -t ubuntu_autonomous_unicycle $THIS_DIR
