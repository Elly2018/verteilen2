#!/usr/bin/env bash

MODULE_CHOICE="$1"
shift 1
EXTRA_ARGS="$@"

echo "Start testing the cmake project"

bash build.sh ${MODULE_CHOICE} ${EXTRA_ARGS}

cd ../../

ctest --output-on-failure