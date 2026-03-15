#!/bin/bash
# Build script for GPU support in keyhunt

echo "Building GPU support for keyhunt..."

# Check if CUDA is available
if ! command -v nvcc &> /dev/null; then
    echo "Error: CUDA compiler (nvcc) not found."
    echo "Please install CUDA Toolkit: https://developer.nvidia.com/cuda-downloads"
    exit 1
fi

# Check CUDA version
CUDA_VERSION=$(nvcc --version | grep "release" | sed 's/.*release //' | sed 's/,.*//')
echo "CUDA version: $CUDA_VERSION"

# Check for GPU
echo "Checking for NVIDIA GPUs..."
nvidia-smi --query-gpu=name,memory.total --format=csv || echo "No NVIDIA GPU detected or nvidia-smi not available"

# Compile GPU code
echo "Compiling GPU kernels..."
nvcc -m64 -O3 -arch=sm_50 -c gpu/kernel.cu -o kernel.o

if [ $? -ne 0 ]; then
    echo "Error: Failed to compile GPU kernels"
    exit 1
fi

# Compile GPU context
echo "Compiling GPU context..."
g++ -m64 -march=native -mtune=native -mssse3 -Wall -Wextra -Wno-deprecated-copy -Ofast -ftree-vectorize -c gpu/gpu.cpp -o gpu.o

if [ $? -ne 0 ]; then
    echo "Error: Failed to compile GPU context"
    exit 1
fi

echo "GPU build complete!"
echo "To build the full keyhunt with GPU support, run: make"
