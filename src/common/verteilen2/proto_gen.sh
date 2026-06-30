#!/bin/bash

mkdir -p proto_gen

cd proto

protoc-c --c_out=./../proto_gen *.proto