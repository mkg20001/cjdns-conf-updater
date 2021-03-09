#!/bin/bash

source $setup

cmake-cross $src \
  -DCMAKE_INSTALL_PREFIX=$out

make
make -j1 install
