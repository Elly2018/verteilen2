#!/bin/bash

echo "Proto files generate start."

# 1. Clean and recreate output directories
rm -rf include/verteilen2/proto_gen src/verteilen2/proto_gen proto_gen
mkdir -p include/verteilen2/proto_gen
mkdir -p src/verteilen2/proto_gen

# Get the absolute path of the proto folder before changing directories
PROTO_DIR="$(pwd)/proto"

# 2. Run protoc from the project root using absolute lookups
# Create a temporary flat folder for protoc to dump the initial structure
mkdir -p proto_gen
find "$PROTO_DIR" -name "*.proto" | xargs protoc --proto_path="$PROTO_DIR" --cpp_out=proto_gen

# 3. Use rsync to copy the headers (.h) while keeping folder layout
# --include="*/" ensures nested folders are scanned and built
# --include="*.h" targets your header generation files
# --exclude="*" drops any other unexpected files out of the pipeline
rsync -a --include="*/" --include="*.h" --exclude="*" proto_gen/ include/verteilen2/proto_gen/

# 4. Use rsync to copy the implementation sources (.cc) while keeping folder layout
rsync -a --include="*/" --include="*.cc" --exclude="*" proto_gen/ src/verteilen2/proto_gen/

# 5. Clean up temporary generation folder completely
rm -rf proto_gen

echo "Proto files generation complete!"