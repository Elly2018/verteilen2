#!/bin/bash

bash build_all_amd64.sh

version=$(< VERSION.txt)

echo "Start packaging: $version"

mkdir -p package/verteilen-2-master
mkdir -p package/verteilen-2-server
mkdir -p package/verteilen-2-client

mkdir -p package/verteilen-2-client/DEBIAN
mkdir -p package/verteilen-2-client/usr/bin
mkdir -p package/verteilen-2-client/usr/share

sed "s|%VV%|$version|g" package/deb_client > package/verteilen-2-client/DEBIAN/control
cp bin/client package/verteilen-2-client/usr/bin/verteilen-2-client
cp -r bin/share/verteilen-2-client package/verteilen-2-client/usr/share/verteilen-2-client

cd package

dpkg-deb --build verteilen-2-client