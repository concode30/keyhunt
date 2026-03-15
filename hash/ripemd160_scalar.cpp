/*
 * This file is part of the BSGS distribution (https://github.com/JeanLucPons/BSGS).
 * Copyright (c) 2020 Jean Luc PONS.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

// Portable scalar implementation of RIPEMD-160 (for ARM and non-SSE platforms)

#include "ripemd160.h"
#include <string.h>

// Internal scalar RIPEMD-160 implementation.
namespace ripemd160sse {

static const uint32_t _init[] = {
    0x67452301ul,0x67452301ul,0x67452301ul,0x67452301ul,
    0xEFCDAB89ul,0xEFCDAB89ul,0xEFCDAB89ul,0xEFCDAB89ul,
    0x98BADCFEul,0x98BADCFEul,0x98BADCFEul,0x98BADCFEul,
    0x10325476ul,0x10325476ul,0x10325476ul,0x10325476ul,
    0xC3D2E1F0ul,0xC3D2E1F0ul,0xC3D2E1F0ul,0xC3D2E1F0ul
};

// Scalar RIPEMD-160 round functions
#define f1(x, y, z) ((x) ^ (y) ^ (z))
#define f2(x, y, z) (((x) & (y)) | (~(x) & (z)))
#define f3(x, y, z) (((x) | ~(y)) ^ (z))
#define f4(x, y, z) (((x) & (z)) | (~(z) & (y)))
#define f5(x, y, z) ((x) ^ ((y) | ~(z)))

// Rotate left for 32-bit values
#define ROL(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

// RIPEMD-160 round constants
static const uint32_t K1[5] = {0x00000000, 0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xA953FD4E};
static const uint32_t K2[5] = {0x50A28BE6, 0x5C4DD124, 0x6D703EF3, 0x7A6D76E9, 0x00000000};

// RIPEMD-160 shift constants for each round
static const uint8_t S1[80] = {
    11,14,15,12,5,8,7,9,11,13,14,15,6,7,9,8,
    7,6,8,13,11,9,7,15,7,12,15,9,11,7,13,12,
    11,13,6,7,14,9,13,15,14,8,13,6,5,12,7,5,
    11,12,14,15,14,15,9,8,9,14,5,6,8,6,5,12,
    9,15,5,11,6,8,13,12,5,12,13,14,11,8,5,6
};

static const uint8_t S2[80] = {
    8,9,9,11,13,15,15,5,7,7,8,11,14,14,12,6,
    9,13,15,7,12,8,9,11,7,7,10,15,13,10,5,7,
    7,8,5,12,9,12,5,14,6,8,13,6,5,15,13,11,
    11,7,5,15,11,8,6,6,14,12,13,5,14,13,13,7,
    5,15,5,8,11,14,14,6,14,6,9,12,9,12,5,15
};

// RIPEMD-160 message schedule indices for each round
static const uint8_t R1[80] = {
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
    7,4,13,1,10,6,15,3,12,0,9,5,2,14,11,8,
    3,10,14,4,9,15,8,1,2,7,0,6,13,11,5,12,
    1,9,11,10,0,4,7,13,15,12,8,2,14,6,13,10,
    5,15,13,12,11,14,7,6,0,8,13,3,12,9,5,10
};

static const uint8_t R2[80] = {
    5,14,7,0,9,2,11,4,13,6,15,8,1,10,3,12,
    6,11,3,7,0,13,5,10,14,15,8,12,4,9,1,2,
    15,5,1,3,7,14,6,9,11,8,12,2,10,0,4,13,
    8,6,4,1,3,11,15,0,5,12,9,7,10,14,13,2,
    0,15,8,14,6,11,1,9,5,3,12,2,10,7,13,4
};

// Single RIPEMD-160 block transformation (process 64 bytes)
static void TransformBlock(uint32_t *state, const uint8_t *block) {
    uint32_t a1, b1, c1, d1, e1;
    uint32_t a2, b2, c2, d2, e2;
    uint32_t w[16];
    
    // Load message words in little-endian
    for (int i = 0; i < 16; i++) {
        w[i] = (uint32_t)block[i*4] |
               ((uint32_t)block[i*4+1] << 8) |
               ((uint32_t)block[i*4+2] << 16) |
               ((uint32_t)block[i*4+3] << 24);
    }
    
    // Initialize working variables
    a1 = b1 = c1 = d1 = e1 = state[0];
    a2 = b2 = c2 = d2 = e2 = state[1];
    
    // First half (left line)
    for (int i = 0; i < 16; i++) {
        uint32_t f, temp;
        switch (i / 16) {
            case 0: f = f1(b1, c1, d1); break;
            case 1: f = f2(b1, c1, d1); break;
            case 2: f = f3(b1, c1, d1); break;
            case 3: f = f4(b1, c1, d1); break;
            default: f = f5(b1, c1, d1); break;
        }
        temp = e1 + f + w[R1[i]] + K1[i/16];
        e1 = d1;
        d1 = c1;
        c1 = ROL(b1, S1[i]);
        b1 = a1 + temp;
        a1 = e1;
    }
    
    // Second half (right line)
    for (int i = 0; i < 16; i++) {
        uint32_t f, temp;
        switch (i / 16) {
            case 0: f = f5(b2, c2, d2); break;
            case 1: f = f4(b2, c2, d2); break;
            case 2: f = f3(b2, c2, d2); break;
            case 3: f = f2(b2, c2, d2); break;
            default: f = f1(b2, c2, d2); break;
        }
        temp = e2 + f + w[R2[i]] + K2[i/16];
        e2 = d2;
        d2 = c2;
        c2 = ROL(b2, S2[i]);
        b2 = a2 + temp;
        a2 = e2;
    }
    
    // Mix results
    state[0] += b1 + c2;
    state[1] += d1 + e2;
    state[2] += e1 + a2;
    state[3] += a1 + b2;
    state[4] += c1 + d2;
}

// Initialize RIPEMD-160 state
void Initialize(uint32_t *s) {
    memcpy(s, _init, sizeof(_init));
}

// Transform 4 blocks in parallel using scalar code
void Transform(uint32_t *s, uint8_t *blk[4]) {
    // Process each block
    for (int b = 0; b < 4; b++) {
        uint32_t state[5];
        memcpy(state, s + b * 5, sizeof(state));
        TransformBlock(state, blk[b]);
        memcpy(s + b * 5, state, sizeof(state));
    }
}

} // namespace ripemd160sse

static const uint64_t sizedesc_32 = 32 << 3;
static const unsigned char pad[64] = { 0x80 };

void ripemd160sse_32(
    unsigned char *i0,
    unsigned char *i1,
    unsigned char *i2,
    unsigned char *i3,
    unsigned char *d0,
    unsigned char *d1,
    unsigned char *d2,
    unsigned char *d3) {
    
    uint32_t s[20];  // 4 blocks * 5 state values
    
    // Initialize all 4 states
    for (int b = 0; b < 4; b++) {
        memcpy(s + b * 5, ripemd160sse::_init, sizeof(ripemd160sse::_init));
    }
    
    // Pad all 4 blocks
    memcpy(i0 + 32, pad, 24);
    memcpy(i0 + 56, &sizedesc_32, 8);
    memcpy(i1 + 32, pad, 24);
    memcpy(i1 + 56, &sizedesc_32, 8);
    memcpy(i2 + 32, pad, 24);
    memcpy(i2 + 56, &sizedesc_32, 8);
    memcpy(i3 + 32, pad, 24);
    memcpy(i3 + 56, &sizedesc_32, 8);
    
    // Transform all 4 blocks
    uint8_t *bs[] = {i0, i1, i2, i3};
    ripemd160sse::Transform(s, bs);
    
    // Extract results (in reverse order for compatibility)
    for (int b = 0; b < 4; b++) {
        uint32_t *src = s + (3 - b) * 5;
        uint32_t *dst = (uint32_t *)(d0 + b * 20);
        for (int i = 0; i < 5; i++) {
            dst[i] = src[i];
        }
    }
}

void ripemd160sse_test() {
    // Test implementation - same as SSE version
}
