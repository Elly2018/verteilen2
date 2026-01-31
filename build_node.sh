#!/bin/bash

mkdir -p bin
mkdir -p bin/node

cd src/node

go build -o ../../bin/node/node