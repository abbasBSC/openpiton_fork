#!/bin/bash

bash -c "
source ./piton/ariane_setup.sh
cd build
rm -rf *
sims -sys=manycore -x_tiles=1 -y_tiles=1 -vlt_build -ariane
cd ../piton/tools/metro_mpi/isa_test
bash ./run_all_isa_test.sh
"