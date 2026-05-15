#!/bin/bash

mkdir build
cd build

cmake ..

cmake --build . -j 8