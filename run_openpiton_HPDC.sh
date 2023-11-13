#!/bin/bash

bash -c "
source ./piton/ariane_setup.sh
cd build
rm -rf *
sims -sys=manycore -x_tiles=1 -y_tiles=1 -config_rtl=PITON_ARIANE_HPDC -l15_num_threads=16 -msm_build -ariane 
sims -sys=manycore -msm_run -x_tiles=1 -y_tiles=1 -config_rtl=PITON_ARIANE_HPDC -l15_num_threads=16 matmul.c -ariane -rtl_timeout 100000000
"