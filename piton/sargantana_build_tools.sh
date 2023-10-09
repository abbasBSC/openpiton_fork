#!/bin/bash

# Author: Oscar Lostes Cazorla <oscar.lostes@bsc.es>, BSC
# Date: 26.11.2018
# Description: This script builds the RISCV toolchain, benchmarks, assembly tests
# the RISCV FESVR and the RISCV Torture framework for OpenPiton+Sargantana configurations.
# Please source the sargantana_setup.sh first.
#
#
# Make sure you have the following packages installed:
#
# sudo apt install \
#          gcc-7 \
#          g++-7 \
#          gperf \
#          autoconf \
#          automake \
#          autotools-dev \
#          libmpc-dev \
#          libmpfr-dev \
#          libgmp-dev \
#          gawk \
#          build-essential \
#          bison \
#          flex \
#          texinfo \
#          python-pexpect \
#          libusb-1.0-0-dev \
#          default-jdk \
#          zlib1g-dev \
#          valgrind \
#          csh


echo
echo "----------------------------------------------------------------------"
echo "building RISCV toolchain and tests (if not existing)"
echo "----------------------------------------------------------------------"
echo

if [[ "${RISCV}" == "" ]]
then
    echo "Please source sargantana_setup.sh first, while being in the root folder."
else

  [ -d ${SARG_ROOT} ] || git submodule update --init --recursive piton/design/chip/tile/sargantana

  # parallel compilation
  export NUM_JOBS=6

  cd ${SARG_ROOT}

  # build the RISCV tests if necessary
  VERSION="7cc76ea83b4f827596158c8ba0763e93da65de8f"
  mkdir -p ${SARG_ROOT}/tmp
  cd tmp

  [ -d riscv-tests ] || git clone https://github.com/riscv/riscv-tests.git
  cd riscv-tests
  git checkout $VERSION
  git submodule update --init --recursive
  autoconf
  mkdir -p build

  # link in adapted syscalls.c such that the benchmarks can be used in the OpenPiton TB
  cd benchmarks/common/
  rm syscalls.c util.h
  ln -s ${PITON_ROOT}/piton/verif/diag/assembly/include/riscv/ariane/syscalls.c
  ln -s ${PITON_ROOT}/piton/verif/diag/assembly/include/riscv/ariane/util.h
  cd -

  cd build
  tmp_dest=$SARG_ROOT/tmp
  if [ -w /tmp ]
  then
    tmp_dest=/tmp
  fi
  ../configure --prefix=$tmp_dest/riscv-tests/build

  make clean
  make isa        -j${NUM_JOBS} > /dev/null
  NUM_TILES=1 make benchmarks -j${NUM_JOBS} > /dev/null
  make install
  cd ${PITON_ROOT}

  echo
  echo "----------------------------------------------------------------------"
  echo "build complete"
  echo "----------------------------------------------------------------------"
  echo

fi
