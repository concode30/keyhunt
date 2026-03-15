# GPU Implementation Guide for keyhunt

## Overview

This document describes the GPU implementation for keyhunt, providing accelerated secp256k1 elliptic curve operations using CUDA.

## Architecture

### GPU Context (gpu/gpu.cpp)

The GPU context manages:
- CUDA device initialization
- Memory allocation and management
- Stream creation for async operations
- Data transfer between host and device

### CUDA Kernels (gpu/kernel.cu)

The kernel file contains CUDA kernels for:
- `computePublicKeyKernel` - Compute public keys from private keys
- `batchScalarMultKernel` - Batch scalar multiplication
- `pointAddKernel` - Batch point addition
- `pointDoubleKernel` - Batch point doubling
- `bsgsPrecomputeKernel` - BSGS table precomputation
- `vanitySearchKernel` - Vanity address search
- `addressMatchKernel` - Address matching with bloom filters

## Key Operations

### Scalar Multiplication

The core operation for EC cryptography is scalar multiplication: Q = k × G

Implemented using double-and-add algorithm with GPU parallelization.

### Point Addition

Point addition on secp256k1 curve:
- P3 = P1 + P2
- Uses projective coordinates for efficiency
- Modular arithmetic optimized for GPU

### Point Doubling

Point doubling: P2 = 2 × P1
- Special case of point addition
- Optimized for secp256k1 curve

## Memory Management

### Host-Device Transfers

Data transfer between CPU and GPU:
- Upload: CPU → GPU (for input data)
- Download: GPU → CPU (for results)

### Buffer Management

GPU uses circular buffers for:
- Input keys
- Intermediate results
- Output public keys

## Performance Optimization

### 1. Batch Processing

Process multiple keys in parallel:
```cuda
batchScalarMultKernel<<<gridSize, blockSize>>>(results, points, scalars, count);
```

### 2. Memory Coalescing

Access patterns optimized for GPU memory:
- Sequential memory access
- Aligned data structures
- Minimize bank conflicts

### 3. Kernel Fusion

Combine operations when possible:
- Compute and check in single kernel
- Reduce memory transfers

## Current Limitations

1. **Partial Implementation**: GPU kernels are stubbed - full implementation needed
2. **Memory Transfer Overhead**: CPU-GPU transfers can bottleneck performance
3. **VRAM Limitations**: Large bloom filters may not fit on GPU

## Future Improvements

1. **Full Kernel Implementation**: Complete secp256k1 operations in CUDA
2. **Zero-Copy Memory**: Use pinned memory for faster transfers
3. **Kernel Fusion**: Combine multiple operations in single kernel
4. **Adaptive Batching**: Dynamic batch size based on GPU capabilities
5. **Multi-GPU Support**: Scale across multiple GPUs

## Debugging

### Enable GPU Debugging

```bash
export CUDA_LAUNCH_BLOCKING=1
```

### Check GPU Memory

```bash
nvidia-smi -q -d MEMORY,POWER
```

### CUDA Debugging Tools

- `cuda-memcheck` - Memory checker
- `nvprof` - Profiler
- `nsight` - Full debugging suite

## Testing

### Basic Test

```bash
./keyhunt -m gpu -f tests/66.txt -b 66 -R -q
```

### Performance Test

```bash
./keyhunt -m gpu -f tests/125.txt -b 125 -R -k 128 -q -s 10
```

## Troubleshooting

### GPU Not Detected

1. Check NVIDIA drivers: `nvidia-smi`
2. Verify CUDA installation: `nvcc --version`
3. Check GPU compatibility: compute capability >= 5.0

### Out of Memory

1. Reduce batch size
2. Use smaller bloom filters
3. Close other GPU applications

### Compilation Errors

1. Ensure CUDA Toolkit is installed
2. Check GPU architecture flag (-arch=sm_XX)
3. Verify GPU supports required CUDA features
