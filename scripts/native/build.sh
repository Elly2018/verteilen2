#!/usr/bin/env bash

MODULE_CHOICE="$1"
shift 1
EXTRA_ARGS="$@"

bash setup.sh ${MODULE_CHOICE} ${EXTRA_ARGS}

echo "Start generate protobuf definitions"

cd ../../src/native/common

bash proto_gen.sh

cd ../../../

cd build/native

echo "Start building the cmake project"

if [[ "$OSTYPE" == "darwin"* ]]; then
    TOTAL_CORES=$(sysctl -n hw.ncpu)
else
    TOTAL_CORES=$(nproc)
fi

BUILD_JOBS=$(( TOTAL_CORES > 1 ? TOTAL_CORES - 1 : 1 ))

cmake --build . -j ${BUILD_JOBS} ${EXTRA_ARGS}

cd ../../scripts/native

bash copy.sh ${MODULE_CHOICE} ${EXTRA_ARGS}