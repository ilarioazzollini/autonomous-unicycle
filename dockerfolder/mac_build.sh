#!/bin/bash

THIS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

docker build -t ubuntu_autonomous_unicycle $THIS_DIR
