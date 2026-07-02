#!/bin/bash

bash setup_all_amd64.sh

cd build

cmake --build . -j 8

cd ..

bash copy_all_resource.sh