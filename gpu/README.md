# GPU Support for keyhunt

This directory contains GPU-accelerated implementations for secp256k1 elliptic curve operations.

## Files

- `gpu.h` - GPU context interface and data structures
- `gpu.cpp` - CPU-side GPU context management
- `kernel.cu` - CUDA kernels for secp256k1 operations

## Building

GPU support requires CUDA Toolkit (nvcc compiler). To build with GPU support:

```bash
make
```

The Makefile automatically detects CUDA and compiles GPU code.

## Usage

To use GPU mode:

```bash
./keyhunt -m gpu -f targets.txt -b 66 -R
```

## Current Status

GPU support is currently in **experimental** state. The implementation provides:

- GPU context management
- CUDA kernel infrastructure for secp256k1 operations
- Thread integration with CPU code

## Implementation Notes

The GPU implementation uses CUDA for parallel computation of:
- Point addition on secp256k1 curve
- Point doubling
- Scalar multiplication
- Hash computation (SHA256, RIPEMD160)

## Requirements

- CUDA Toolkit 10.0 or later
- NVIDIA GPU with compute capability 5.0 or higher
- At least 4GB VRAM recommended

## Performance

GPU performance depends on:
- GPU model and VRAM
- Number of concurrent threads
- Memory transfer overhead
- Kernel optimization

Expected speedup: 2-10x depending on GPU and workload.
