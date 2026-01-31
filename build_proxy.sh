#!/bin/bash

mkdir -p bin
mkdir -p bin/proxy

cd src/proxy

echo Building proxy linux amd64
env GOOS=linux GOARCH=amd64 go build -o ../../bin/proxy/proxy_amd64_linux
echo Building proxy linux arm64
env GOOS=linux GOARCH=arm64 go build -o ../../bin/proxy/proxy_arm64_linux
echo Building proxy windows amd64
env GOOS=windows GOARCH=amd64 go build -o ../../bin/proxy/proxy_amd64_windows.exe
echo Building proxy darwin amd64
env GOOS=darwin GOARCH=amd64 go build -o ../../bin/proxy/proxy_amd64_osx