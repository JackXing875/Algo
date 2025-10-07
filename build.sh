#!/bin/bash

BUILD_DIR="build"

if [ ! -d "$BUILD_DIR" ] || [ ! -f "$BUILD_DIR/build.ninja" ]; then
    echo "GENERATING NINJA BUILD FILES..."
    cmake -B "$BUILD_DIR" -S .
fi

# 编译项目
echo "COMPILATION IN PROGRESS..."
cmake --build "$BUILD_DIR"

# 编译完成提示
echo "COMPILATION COMPLETED"
