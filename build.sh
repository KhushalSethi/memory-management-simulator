#!/bin/bash
# Simple build script for Memory Management Simulator

echo "Building Memory Management Simulator..."

# Create build directory
mkdir -p build
cd build

# Run CMake
cmake ..

# Build the project
make

echo "Build complete! Executable is in build/bin/memsim"
echo "To run: ./build/bin/memsim"
