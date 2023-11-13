#!/bin/bash

bash -c "
source ./piton/ariane_setup.sh
cd build
rm -rf *
sims -sys=manycore -x_tiles=1 -y_tiles=1 -l15_num_threads=16 -vlt_build -ariane
sims -sys=manycore -vlt_run -x_tiles=1 -y_tiles=1 -l15_num_threads=16 hello_world.c -ariane -rtl_timeout 100000000
"