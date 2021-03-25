#!/bin/bash

mkdir build

cmake -B build

cd build

make

sudo ./idps
