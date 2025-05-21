#!/bin/bash

mkdir -p build && cd build
cmake ..
cmake --build .
mv convert_grayscale ..
cd ..
echo "Build complete and 'convert_grayscale' moved to the parent directory."
