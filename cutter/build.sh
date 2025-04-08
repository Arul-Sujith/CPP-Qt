#!/bin/bash

set -e

BUILD_DIR="build"

if [ -d "$BUILD_DIR" ]; then
    echo "Cleaning previous build..."
    rm -rf "$BUILD_DIR"
fi

mkdir "$BUILD_DIR"
cd "$BUILD_DIR"

echo "Configuring project with CMake..."
cmake ..

echo "Building project..."
make -j$(nproc)

echo "🚀 Running CutterMock..."
./CutterMock
