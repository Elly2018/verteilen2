#!/bin/bash

echo "Proto files generate start."

# 1. Clean and recreate output directories
rm -rf include/verteilen2/proto_gen src/verteilen2/proto_gen proto_gen
mkdir -p include/verteilen2/proto_gen
mkdir -p src/verteilen2/proto_gen

# Get the absolute path of the proto folder
PROTO_DIR="$(pwd)/proto"

# 2. Run protoc from the project root using absolute lookups
mkdir -p proto_gen
find "$PROTO_DIR" -name "*.proto" | xargs protoc --proto_path="$PROTO_DIR" --cpp_out=proto_gen

# 3. PRESERVE STRUCTURE: Move files while retaining their directories
cd proto_gen

# Find all headers and mirror their exact directories to target include folder
find . -name "*.h" -exec cp --parents {} ../include/verteilen2/proto_gen/ \;

# Find all implementation files and mirror their exact directories to target src folder
find . -name "*.cc" -exec cp --parents {} ../src/verteilen2/proto_gen/ \;

cd ..

# 4. Clean up temporary generation folder
rm -rf proto_gen

echo "Proto files generation complete with intact folder layout!"