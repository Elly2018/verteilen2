#!/bin/bash

echo "Proto files generate start."

rm -rf include/verteilen2/proto_gen src/verteilen2/proto_gen proto_gen
mkdir -p include/verteilen2/proto_gen src/verteilen2/proto_gen

mkdir -p proto_gen
cd proto
protoc *.proto --cpp_out="../proto_gen"
cd ..

cd proto_gen
cp *.h ../include/verteilen2/proto_gen
cp *.cc ../src/verteilen2/proto_gen
cd ..

rm -rf proto_gen
echo "Proto files generation complete!"