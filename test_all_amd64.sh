#!/bin/bash

mkdir build
cd build

cmake ..

cmake --build . -j 8
ctest --output-on-failure