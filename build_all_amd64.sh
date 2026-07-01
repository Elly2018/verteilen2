#!/bin/bash

source setup_all_amd64.sh

cmake --build . -j 8

source copy_all_resource.sh