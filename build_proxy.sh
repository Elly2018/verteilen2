#!/bin/bash

mkdir -p bin
mkdir -p bin/proxy

cd src/proxy

go build -o ../../bin/proxy/proxy