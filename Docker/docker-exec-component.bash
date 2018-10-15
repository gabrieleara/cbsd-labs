#!/bin/bash

set -e

# Assuming there is only one container running
docker exec -ti $(docker container list -q) bash
