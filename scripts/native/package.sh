#!/usr/bin/env bash

MODULE_CHOICE="$1"
shift 1
EXTRA_ARGS="$@"

bash build.sh ${MODULE_CHOICE} ${EXTRA_ARGS}

cd ../..

version=$(< VERSION.txt)

echo "Start packaging the cmake projects: ${version}"

if [[ "${MODULE_CHOICE}" == "all" ]]; then
    ALL_ON="true"
else
    ALL_ON="false"
fi

if [[ "$ALL_ON" == "true" ]] || [[ "${MODULE_CHOICE}" == "client" ]]; then
    CLIENT_ON="true"
else
    CLIENT_ON="false"
fi

if [[ "$ALL_ON" == "true" ]] || [[ "${MODULE_CHOICE}" == "master" ]]; then
    MASTER_ON="true"
else
    MASTER_ON="false"
fi

if [[ "$ALL_ON" == "true" ]] || [[ "${MODULE_CHOICE}" == "server" ]]; then
    SERVER_ON="true"
else
    SERVER_ON="false"
fi

if [[ "${CLIENT_ON}" == "true" ]]; then
    mkdir -p package/verteilen-2-client
    mkdir -p package/verteilen-2-client/DEBIAN
    mkdir -p package/verteilen-2-client/usr/bin
    mkdir -p package/verteilen-2-client/usr/share

    sed "s|%VV%|$version|g" package/deb_client > package/verteilen-2-client/DEBIAN/control
    cp bin/bin/client package/verteilen-2-client/usr/bin/verteilen-2-client
    cp -r bin/bin/share/verteilen-2-client package/verteilen-2-client/usr/share/verteilen-2-client

    cd package
    dpkg-deb --build verteilen-2-client
    cd ..
fi

if [[ "${MASTER_ON}" == "true" ]]; then
    mkdir -p package/verteilen-2-master
    mkdir -p package/verteilen-2-master/DEBIAN
    mkdir -p package/verteilen-2-master/usr/bin
    mkdir -p package/verteilen-2-master/usr/share

    sed "s|%VV%|$version|g" package/deb_master > package/verteilen-2-master/DEBIAN/control
    cp bin/bin/master package/verteilen-2-master/usr/bin/verteilen-2-master
    cp -r bin/bin/share/verteilen-2-master package/verteilen-2-master/usr/share/verteilen-2-master

    cd package
    dpkg-deb --build verteilen-2-master
    cd ..
fi

if [[ "${SERVER_ON}" == "true" ]]; then
    mkdir -p package/verteilen-2-server
    mkdir -p package/verteilen-2-server/DEBIAN
    mkdir -p package/verteilen-2-server/usr/bin
    mkdir -p package/verteilen-2-server/usr/share

    sed "s|%VV%|$version|g" package/deb_server > package/verteilen-2-server/DEBIAN/control
    cp bin/bin/server package/verteilen-2-server/usr/bin/verteilen-2-server
    cp -r bin/bin/share/verteilen-2-server package/verteilen-2-server/usr/share/verteilen-2-server

    cd package
    dpkg-deb --build verteilen-2-server
    cd ..
fi
