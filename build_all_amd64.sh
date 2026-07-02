#!/bin/bash

bash setup_all_amd64.sh

cd src/common/verteilen2

bash proto_gen.sh

cd ../../../

cd build

cmake --build . -j 8

cd ..

bash copy_all_resource.sh