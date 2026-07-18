#!/usr/bin/env bash

MODULE_CHOICE="$1"
shift 1
EXTRA_ARGS="$@"

echo "Start setup the cmake project"

cd ../../

mkdir -p build/native

cd build/native

if [[ "${MODULE_CHOICE}" == "all" ]]; then
    args="-D ENABLE_CLI=ON -D ENABLE_CLIENT=ON -D ENABLE_COMMON=ON -D ENABLE_MASTER=ON -D ENABLE_SERVER=ON"
fi

if [[ "${MODULE_CHOICE}" == "cli" ]]; then
    args="-D ENABLE_CLI=ON"
fi

if [[ "${MODULE_CHOICE}" == "client" ]]; then
    args="-D ENABLE_CLIENT=ON"
fi

if [[ "${MODULE_CHOICE}" == "common" ]]; then
    args="-D ENABLE_COMMON=ON"
fi

if [[ "${MODULE_CHOICE}" == "master" ]]; then
    args="-D ENABLE_MASTER=ON"
fi

if [[ "${MODULE_CHOICE}" == "server" ]]; then
    args="-D ENABLE_SERVER=ON"
fi

cmake ../.. ${args} ${EXTRA_ARGS}