/*
 * GPU support for keyhunt
 * CPU-side implementation of GPU context management
 */

#include "gpu.h"
#include <iostream>
#include <cstring>

#ifdef __CUDACC__
#include <cuda_runtime.h>
#else
// Fallback when CUDA is not available
#define cudaSuccess 0
#endif

GPUContext::GPUContext() : initialized(false), cudaContext(nullptr), 
                           stream(nullptr), d_points(nullptr), d_scalars(nullptr),
                           d_results(nullptr), allocatedMemory(0) {
}

GPUContext::~GPUContext() {
    if (initialized) {
        // Free GPU memory
        if (d_points) {
#ifdef __CUDACC__
            cudaFree(d_points);
#endif
            allocatedMemory -= allocatedMemory; // approximate
        }
        if (d_scalars) {
#ifdef __CUDACC__
            cudaFree(d_scalars);
#endif
        }
        if (d_results) {
#ifdef __CUDACC__
            cudaFree(d_results);
#endif
        }
#ifdef __CUDACC__
        cudaDeviceReset();
#endif
    }
}

bool GPUContext::Init() {
#ifdef __CUDACC__
    int deviceCount = 0;
    cudaError_t err = cudaGetDeviceCount(&deviceCount);
    
    if (err != cudaSuccess || deviceCount == 0) {
        std::cerr << "[!] No CUDA devices found" << std::endl;
        return false;
    }
    
    // Use device 0 by default
    err = cudaSetDevice(0);
    if (err != cudaSuccess) {
        std::cerr << "[!] Failed to set CUDA device" << std::endl;
        return false;
    }
    
    // Create CUDA stream for async operations
    err = cudaStreamCreate(&stream);
    if (err != cudaSuccess) {
        std::cerr << "[!] Failed to create CUDA stream" << std::endl;
        return false;
    }
    
    initialized = true;
    return true;
#else
    std::cerr << "[!] CUDA not available, GPU support disabled" << std::endl;
    return false;
#endif
}

GPUInfo GPUContext::GetInfo() {
    GPUInfo info;
    memset(&info, 0, sizeof(info));
    
#ifdef __CUDACC__
    cudaDeviceProp prop;
    cudaError_t err = cudaGetDeviceProperties(&prop, 0);
    
    if (err == cudaSuccess) {
        info.deviceCount = 1;
        info.currentDevice = 0;
        info.totalMemory = prop.totalGlobalMem;
        info.freeMemory = prop.totalGlobalMem - prop.sharedMemPerBlock;
        strncpy(info.name, prop.name, sizeof(info.name) - 1);
    }
#endif
    
    return info;
}

bool GPUContext::IsAvailable() {
    return initialized;
}

Point GPUContext::ComputePublicKeyGPU(Int* privKey) {
    Point result;
    // Placeholder - actual implementation in CUDA kernel
    return result;
}

std::vector<Point> GPUContext::ComputePublicKeysGPU(std::vector<Int>* privKeys) {
    std::vector<Point> results;
    // Placeholder - actual implementation in CUDA kernel
    return results;
}

Point GPUContext::AddGPU(Point& p1, Point& p2) {
    Point result;
    // Placeholder - actual implementation in CUDA kernel
    return result;
}

Point GPUContext::DoubleGPU(Point& p) {
    Point result;
    // Placeholder - actual implementation in CUDA kernel
    return result;
}

Point GPUContext::ScalarMultGPU(Point& P, Int* scalar) {
    Point result;
    // Placeholder - actual implementation in CUDA kernel
    return result;
}

bool GPUContext::UploadData(void* data, size_t size) {
#ifdef __CUDACC__
    if (d_points) cudaFree(d_points);
    cudaError_t err = cudaMalloc(&d_points, size);
    if (err != cudaSuccess) return false;
    
    err = cudaMemcpy(d_points, data, size, cudaMemcpyHostToDevice);
    return err == cudaSuccess;
#else
    return false;
#endif
}

bool GPUContext::DownloadData(void* data, size_t size) {
#ifdef __CUDACC__
    if (!d_results) return false;
    
    cudaError_t err = cudaMemcpy(data, d_results, size, cudaMemcpyDeviceToHost);
    return err == cudaSuccess;
#else
    return false;
#endif
}

void GPUContext::Sync() {
#ifdef __CUDACC__
    cudaStreamSynchronize(stream);
#endif
}

size_t GPUContext::GetMemoryUsage() {
    return allocatedMemory;
}

GPUContext* CreateGPUContext() {
    return new GPUContext();
}

void DestroyGPUContext(GPUContext* ctx) {
    if (ctx) {
        delete ctx;
    }
}
