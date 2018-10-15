#!/bin/bash

set -e 

docker run -ti --network host --mount type=bind,source="$HOME/Documents/Component/Labs",target="/home/coder/cbsd-lab" gabrieleara/cbsd
