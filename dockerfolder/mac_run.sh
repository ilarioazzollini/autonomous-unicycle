#!/bin/bash

THIS_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null && pwd )"

docker run -it --rm \
    -v $THIS_DIR/..:/root/autonomous-unicycle \
    ubuntu_autonomous_unicycle \
    bash
