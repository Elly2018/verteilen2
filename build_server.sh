#!/bin/bash

mkdir -p bin
mkdir -p bin/server

cd src/server

go build -o ../../bin/server/server