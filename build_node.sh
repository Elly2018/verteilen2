#!/bin/bash

mkdir -p bin
mkdir -p bin/node

cd src/node

echo Building node linux amd64
env GOOS=linux GOARCH=amd64 go build -o ../../bin/node/node_amd64_linux
echo Building node linux arm64
env GOOS=linux GOARCH=arm64 go build -o ../../bin/node/node_arm64_linux
echo Building node windows amd64
env GOOS=windows GOARCH=amd64 go build -o ../../bin/node/node_amd64_windows.exe
echo Building node darwin amd64
env GOOS=darwin GOARCH=amd64 go build -o ../../bin/node/node_amd64_osx