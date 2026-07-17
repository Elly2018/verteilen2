#!/usr/bin/env bash

echo $@
exit 0

echo "Start setup the cmake project"

cd ../../

mkdir -p build/native

cd build/native

cmake ../..