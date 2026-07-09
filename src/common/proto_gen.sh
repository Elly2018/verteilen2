#!/bin/bash

echo "Proto files generate start."

# 1. Clean and recreate output directories
rm -rf include/verteilen2/proto_gen src/verteilen2/proto_gen proto_gen
mkdir -p proto_gen
mkdir -p include/verteilen2/proto_gen
mkdir -p src/verteilen2/proto_gen

# Get the absolute path of the proto folder before changing directories
PROTO_DIR="$(pwd)/proto"

# 2. Run protoc from the project root using absolute lookups
# --proto_path="$PROTO_DIR" sets the global import root
# The second entry tells protoc where to look for local file execution context
find "$PROTO_DIR" -name "*.proto" | xargs protoc --proto_path="$PROTO_DIR" --cpp_out=proto_gen

# 3. Recursively find and move all generated headers (.pb.h)
find proto_gen -name "*.h" -exec mv {} include/verteilen2/proto_gen/ \;

# 4. Recursively find and move all generated sources (.pb.cc)
find proto_gen -name "*.cc" -exec mv {} src/verteilen2/proto_gen/ \;

# 5. Clean up temporary generation folder
rm -rf proto_gen

echo "Proto files generation complete!"