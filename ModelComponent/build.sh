#!/bin/bash

mkdir build

sudo apt-get install libzmq3-dev
cmake -B build

cd build

make

sudo ./idps
