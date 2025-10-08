#!/bin/bash
set -e

BUILD_DIR="build"

# 若没有构建目录或构建文件，则重新生成
if [ ! -d "$BUILD_DIR" ] || [ ! -f "$BUILD_DIR/build.ninja" ]; then
    echo "Generating build files..."
    cmake -S . -B "$BUILD_DIR" -G Ninja
fi

# 编译
echo "Building project..."
cmake --build "$BUILD_DIR" --parallel

echo "Build finished successfully."
