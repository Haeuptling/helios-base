#!/bin/bash

#./rcssmonitor/src/rcssmonitor &
./rcssserver-19.0.0/src/rcssserver --server::auto_mode=true &
./helios-base/src/start.sh &
./helios-base2/src/start.sh &

wait

