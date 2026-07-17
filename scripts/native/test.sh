#!/usr/bin/env bash

bash build_all_amd64.sh

echo "Execute all unit tests"

ctest --output-on-failure