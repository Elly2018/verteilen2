#!/bin/bash

if [ "$(basename "$PWD")" != "build" ]; then
    cd build
fi  

echo "Trying to copy all static resources"

echo "pwd: $(basename "$PWD")"

mkdir -p ../bin/share/verteilen-2-master
mkdir -p ../bin/share/verteilen-2-server
mkdir -p ../bin/share/verteilen-2-client

cp -r ../src/master/static/* ../bin/share/verteilen-2-master/
cp -r ../src/server/static/* ../bin/share/verteilen-2-server/
cp -r ../src/client/static/* ../bin/share/verteilen-2-client/