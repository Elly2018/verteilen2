#!/bin/bash

mkdir -p bin
mkdir -p bin/server
mkdir -p bin/server/static

cd src/web

echo Building web files
npm run build:bin