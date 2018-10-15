#!/bin/bash

set -e

# Downloading the container
docker pull gabrieleara/cbsd

# Get the directory in which the script resides
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" > /dev/null && pwd )"

# Linking commands to bin
sudo ln -s "$DIR/docker-run-component.bash" /usr/local/bin/
sudo ln -s "$DIR/docker-exec-component.bash" /usr/local/bin/
