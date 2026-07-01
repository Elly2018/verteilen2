#!/bin/bash

if [ "$(basename "$PWD")" != "build" ]; then
    cd build
fi  

mkdir -p ../bin/static/master
mkdir -p ../bin/static/server
mkdir -p ../bin/static/client

cp -r ../src/master/static/* ../bin/static/master/
cp -r ../src/server/static/* ../bin/static/server/
cp -r ../src/client/static/* ../bin/static/client/