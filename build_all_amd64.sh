#!/bin/bash

source setup_all_amd64.sh

cmake --build . -j 8

mkdir -p ../bin/static/master
mkdir -p ../bin/static/server
mkdir -p ../bin/static/client

cp -r ../src/master/static/* ../bin/static/master/
cp -r ../src/server/static/* ../bin/static/server/
cp -r ../src/client/static/* ../bin/static/client/