#!/bin/bash

mkdir -p bin
mkdir -p bin/server
mkdir -p bin/server/static

cd src/web

npm run build:bin