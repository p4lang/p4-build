#!/bin/bash
set -e
git clone https://github.com/p4lang/behavioral-model.git bmv2_tmp
cd bmv2_tmp
./autogen.sh
./configure 'CXX=g++-4.8' 'CXXFLAGS=-O0' --with-pdfixed --prefix=$HOME/bmv2
make -j2
make install
cd ..
rm -rf bmv2_tmp
