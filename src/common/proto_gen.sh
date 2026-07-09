#!/bin/bash

echo "Proto files generate start."

# 1. Clean and recreate a single target directory
rm -rf include/verteilen2/proto_gen src/verteilen2/proto_gen proto_gen
mkdir -p src/verteilen2/proto_gen

PROTO_DIR="$(pwd)/proto"

# 2. Run protoc
mkdir -p proto_gen
find "$PROTO_DIR" -name "*.proto" | xargs protoc --proto_path="$PROTO_DIR" --cpp_out=proto_gen

# 3. Copy EVERYTHING (.h and .cc) into the src folder, keeping the structure intact
cd proto_gen
find . -name "*.h" -exec cp --parents {} ../src/verteilen2/proto_gen/ \;
find . -name "*.cc" -exec cp --parents {} ../src/verteilen2/proto_gen/ \;
cd ..

rm -rf proto_gen
echo "Proto files generation complete!"