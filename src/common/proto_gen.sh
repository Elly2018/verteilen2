#!/bin/bash

mkdir -p proto_gen
mkdir -p include/verteilen2/proto_gen
mkdir -p src/verteilen2/proto_gen

cd proto

protoc-c --c_out=./../proto_gen *.proto

cd ..

mv ./proto_gen/*.h include/verteilen2/proto_gen

mv ./proto_gen/*.c src/verteilen2/proto_gen

rm -rf proto_gen