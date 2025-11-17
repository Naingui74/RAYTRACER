#!/bin/bash

set -e

if [ -d "build" ]; then
    echo "Removing existing build directory..."
    rm -rf build
fi

echo "🛠️  Creating build directory..."
mkdir -p build
cd build

echo "⚙️  Running cmake..."
cmake ..

echo "🔨 Building project Ouiiiiii"
if [[ "$OSTYPE" == "darwin"* ]]; then
    make -j$(sysctl -n hw.ncpu)
else
    make -j$(nproc)
fi

echo "✅ Build complete! Executable is ready."
