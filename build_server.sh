#!/bin/bash

mkdir -p bin
mkdir -p bin/server

cd src/server

echo Building server linux amd64
env GOOS=linux GOARCH=amd64 go build -o ../../bin/server/server_amd64_linux
echo Building server linux arm64
env GOOS=linux GOARCH=arm64 go build -o ../../bin/server/server_arm64_linux
echo Building server windows amd64
env GOOS=windows GOARCH=amd64 go build -o ../../bin/server/server_amd64_windows.exe
echo Building server darwin amd64
env GOOS=darwin GOARCH=amd64 go build -o ../../bin/server/server_amd64_osx
