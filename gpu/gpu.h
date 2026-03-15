/*
 * GPU support for keyhunt
 * Provides CUDA-based secp256k1 operations
 */

#ifndef GPU_H
#define GPU_H

#include "../secp256k1/Point.h"
#include "../secp256k1/Int.h"
#include <vector>

// GPU device information
struct GPUInfo {
    int deviceCount;
    int currentDevice;
    size_t totalMemory;
    size_t freeMemory;
    char name[256];
};

// GPU context for keyhunt
class GPUContext {
public:
    GPUContext();
    ~GPUContext();
    
    // Initialize GPU
    bool Init();
    
    // Get GPU information
    GPUInfo GetInfo();
    
    // Check if GPU is available
    bool IsAvailable();
    
    // Compute public key on GPU
    Point ComputePublicKeyGPU(Int* privKey);
    
    // Batch public key computation
    std::vector<Point> ComputePublicKeysGPU(std::vector<Int>* privKeys);
    
    // Point addition on GPU
    Point AddGPU(Point& p1, Point& p2);
    
    // Point doubling on GPU
    Point DoubleGPU(Point& p);
    
    // Scalar multiplication on GPU
    Point ScalarMultGPU(Point& P, Int* scalar);
    
    // Transfer data to GPU
    bool UploadData(void* data, size_t size);
    
    // Download data from GPU
    bool DownloadData(void* data, size_t size);
    
    // Synchronize GPU
    void Sync();
    
    // Get GPU memory usage
    size_t GetMemoryUsage();

private:
    bool initialized;
    void* cudaContext;
    void* stream;
    
    // GPU memory buffers
    void* d_points;
    void* d_scalars;
    void* d_results;
    
    size_t allocatedMemory;
};

// GPU kernel launch parameters
struct GPUKernelParams {
    int blockSize;
    int gridSize;
    int threadsPerBlock;
    int blocksPerGrid;
};

// Create GPU context
GPUContext* CreateGPUContext();

// Destroy GPU context
void DestroyGPUContext(GPUContext* ctx);

#endif // GPU_H
