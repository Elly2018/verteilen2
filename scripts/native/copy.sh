#!/usr/bin/env bash

MODULE_CHOICE="$1"
shift 1
EXTRA_ARGS="$@"

echo "Start copy native resources"

cd ../..

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
    mkdir -p bin/native/share/verteilen-2-client
    cp -r src/native/client/static/* bin/native/share/verteilen-2-client/
fi

if [[ "${MASTER_ON}" == "true" ]]; then
    mkdir -p bin/native/share/verteilen-2-master
    cp -r src/native/master/static/* bin/native/share/verteilen-2-master/
fi

if [[ "${SERVER_ON}" == "true" ]]; then
    mkdir -p bin/native/share/verteilen-2-server
    cp -r src/native/server/static/* bin/native/share/verteilen-2-server/
fi