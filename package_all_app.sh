#!/bin/bash

source build_all_amd64.sh

cd ..

echo "Start packaging"

mkdir -p package/master
mkdir -p package/server
mkdir -p package/client

mkdir -p package/client/usr/bin
mkdir -p package/client/usr/share

cp bin/client package/client/usr/bin/verteilen-2-client
cp -r bin/static/client package/client/usr/share/verteilen-2-client

cd package/client



dpkg-deb --build go_pro_control_master