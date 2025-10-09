#!/bin/bash

BUILD_DIR="build"

echo "Building project..."

if [ ! -d "$BUILD_DIR" ] || [ ! -f "$BUILD_DIR/build.ninja" ]; then
    echo "Generating build files..."
    cmake -B "$BUILD_DIR" -S . -G Ninja
else
    cmake -B "$BUILD_DIR" -S . -G Ninja
fi

ninja -C "$BUILD_DIR"
