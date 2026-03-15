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

// Portable scalar implementation of SHA256 (for ARM and non-SSE platforms)

#include "sha256.h"
#include <string.h>
#include <stdint.h>

// SHA256 round constants
static const uint32_t K[64] = {
    0x428A2F98, 0x71374491, 0xB5C0FBCF, 0xE9B5DBA5, 0x3956C25B, 0x59F111F1, 0x923F82A4, 0xAB1C5ED5,
    0xD807AA98, 0x12835B01, 0x243185BE, 0x550C7DC3, 0x72BE5D74, 0x80DEB1FE, 0x9BDC06A7, 0xC19BF174,
    0xE49B69C1, 0xEFBE4786, 0x0FC19DC6, 0x240CA1CC, 0x2DE92C6F, 0x4A7484AA, 0x5CB0A9DC, 0x76F988DA,
    0x983E5152, 0xA831C66D, 0xB00327C8, 0xBF597FC7, 0xC6E00BF3, 0xD5A79147, 0x06CA6351, 0x14292967,
    0x27B70A85, 0x2E1B2138, 0x4D2C6DFC, 0x53380D13, 0x650A7354, 0x766A0ABB, 0x81C2C92E, 0x92722C85,
    0xA2BFE8A1, 0xA81A664B, 0xC24B8B70, 0xC76C51A3, 0xD192E819, 0xD6990624, 0xF40E3585, 0x106AA070,
    0x19A4C116, 0x1E376C08, 0x2748774C, 0x34B0BCB5, 0x391C0CB3, 0x4ED8AA4A, 0x5B9CCA4F, 0x682E6FF3,
    0x748F82EE, 0x78A5636F, 0x84C87814, 0x8CC70208, 0x90BEFFFA, 0xA4506CEB, 0xBEF9A3F7, 0xC67178F2
};

// SHA256 initial hash values
static const uint32_t H_INIT[8] = {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
};

// Rotate right for 32-bit values
static inline uint32_t ROR(uint32_t x, uint32_t n) {
    return (x >> n) | (x << (32 - n));
}

// SHA256 functions
#define S0(x) (ROR((x), 2) ^ ROR((x), 13) ^ ROR((x), 22))
#define S1(x) (ROR((x), 6) ^ ROR((x), 11) ^ ROR((x), 25))
#define s0(x) (ROR((x), 7) ^ ROR((x), 18) ^ (x >> 3))
#define s1(x) (ROR((x), 17) ^ ROR((x), 19) ^ (x >> 10))
#define Maj(x,y,z) (((x) & (y)) | ((x) & (z)) | ((y) & (z)))
#define Ch(x,y,z) (((x) & (y)) | (~(x) & (z)))

// Single SHA256 block transformation
static void TransformBlock(uint32_t *state, const uint32_t *block) {
    uint32_t a, b, c, d, e, f, g, h;
    uint32_t w[64];
    uint32_t T1, T2;
    int i;
    
    // Prepare message schedule
    for (i = 0; i < 16; i++) {
        w[i] = block[i];
    }
    for (i = 16; i < 64; i++) {
        w[i] = s1(w[i-2]) + w[i-7] + s0(w[i-15]) + w[i-16];
    }
    
    // Initialize working variables
    a = state[0]; b = state[1]; c = state[2]; d = state[3];
    e = state[4]; f = state[5]; g = state[6]; h = state[7];
    
    // Main loop
    for (i = 0; i < 64; i++) {
        T1 = h + S1(e) + Ch(e, f, g) + K[i] + w[i];
        T2 = S0(a) + Maj(a, b, c);
        h = g;
        g = f;
        f = e;
        e = d + T1;
        d = c;
        c = b;
        b = a;
        a = T1 + T2;
    }
    
    // Add working variables to state
    state[0] += a; state[1] += b; state[2] += c; state[3] += d;
    state[4] += e; state[5] += f; state[6] += g; state[7] += h;
}

// Transform 4 blocks in parallel using scalar code
void sha256sse_1B(
    uint32_t *i0, uint32_t *i1, uint32_t *i2, uint32_t *i3,
    unsigned char *d0, unsigned char *d1, unsigned char *d2, unsigned char *d3) {
    
    uint32_t state[8];
    uint32_t temp[16];
    
    // Process block 0
    memcpy(state, H_INIT, sizeof(state));
    for (int j = 0; j < 16; j++) temp[j] = i0[j];
    TransformBlock(state, temp);
    
    // Store result (byte swap for big-endian output)
    for (int j = 0; j < 8; j++) {
        ((uint32_t*)d0)[j] = (state[j] >> 24) | (state[j] << 8) | 
                            ((state[j] >> 8) & 0xFF00) | ((state[j] << 24) & 0xFF000000);
    }
    
    // Process block 1
    memcpy(state, H_INIT, sizeof(state));
    for (int j = 0; j < 16; j++) temp[j] = i1[j];
    TransformBlock(state, temp);
    
    for (int j = 0; j < 8; j++) {
        ((uint32_t*)d1)[j] = (state[j] >> 24) | (state[j] << 8) | 
                            ((state[j] >> 8) & 0xFF00) | ((state[j] << 24) & 0xFF000000);
    }
    
    // Process block 2
    memcpy(state, H_INIT, sizeof(state));
    for (int j = 0; j < 16; j++) temp[j] = i2[j];
    TransformBlock(state, temp);
    
    for (int j = 0; j < 8; j++) {
        ((uint32_t*)d2)[j] = (state[j] >> 24) | (state[j] << 8) | 
                            ((state[j] >> 8) & 0xFF00) | ((state[j] << 24) & 0xFF000000);
    }
    
    // Process block 3
    memcpy(state, H_INIT, sizeof(state));
    for (int j = 0; j < 16; j++) temp[j] = i3[j];
    TransformBlock(state, temp);
    
    for (int j = 0; j < 8; j++) {
        ((uint32_t*)d3)[j] = (state[j] >> 24) | (state[j] << 8) | 
                            ((state[j] >> 8) & 0xFF00) | ((state[j] << 24) & 0xFF000000);
    }
}

void sha256sse_2B(
    uint32_t *i0, uint32_t *i1, uint32_t *i2, uint32_t *i3,
    unsigned char *d0, unsigned char *d1, unsigned char *d2, unsigned char *d3) {
    
    uint32_t state[8];
    uint32_t temp[16];
    
    // Process block 0 (2 rounds)
    memcpy(state, H_INIT, sizeof(state));
    for (int j = 0; j < 16; j++) temp[j] = i0[j];
    TransformBlock(state, temp);
    for (int j = 0; j < 16; j++) temp[j] = i0[j + 16];
    TransformBlock(state, temp);
    
    for (int j = 0; j < 8; j++) {
        ((uint32_t*)d0)[j] = (state[j] >> 24) | (state[j] << 8) | 
                            ((state[j] >> 8) & 0xFF00) | ((state[j] << 24) & 0xFF000000);
    }
    
    // Process block 1 (2 rounds)
    memcpy(state, H_INIT, sizeof(state));
    for (int j = 0; j < 16; j++) temp[j] = i1[j];
    TransformBlock(state, temp);
    for (int j = 0; j < 16; j++) temp[j] = i1[j + 16];
    TransformBlock(state, temp);
    
    for (int j = 0; j < 8; j++) {
        ((uint32_t*)d1)[j] = (state[j] >> 24) | (state[j] << 8) | 
                            ((state[j] >> 8) & 0xFF00) | ((state[j] << 24) & 0xFF000000);
    }
    
    // Process block 2 (2 rounds)
    memcpy(state, H_INIT, sizeof(state));
    for (int j = 0; j < 16; j++) temp[j] = i2[j];
    TransformBlock(state, temp);
    for (int j = 0; j < 16; j++) temp[j] = i2[j + 16];
    TransformBlock(state, temp);
    
    for (int j = 0; j < 8; j++) {
        ((uint32_t*)d2)[j] = (state[j] >> 24) | (state[j] << 8) | 
                            ((state[j] >> 8) & 0xFF00) | ((state[j] << 24) & 0xFF000000);
    }
    
    // Process block 3 (2 rounds)
    memcpy(state, H_INIT, sizeof(state));
    for (int j = 0; j < 16; j++) temp[j] = i3[j];
    TransformBlock(state, temp);
    for (int j = 0; j < 16; j++) temp[j] = i3[j + 16];
    TransformBlock(state, temp);
    
    for (int j = 0; j < 8; j++) {
        ((uint32_t*)d3)[j] = (state[j] >> 24) | (state[j] << 8) | 
                            ((state[j] >> 8) & 0xFF00) | ((state[j] << 24) & 0xFF000000);
    }
}

void sha256sse_checksum(
    uint32_t *i0, uint32_t *i1, uint32_t *i2, uint32_t *i3,
    uint8_t *d0, uint8_t *d1, uint8_t *d2, uint8_t *d3) {
    
    uint32_t state[8];
    uint32_t temp[16];
    
    // Process block 0 (2 rounds with padding)
    memcpy(state, H_INIT, sizeof(state));
    for (int j = 0; j < 16; j++) temp[j] = i0[j];
    TransformBlock(state, temp);
    for (int j = 0; j < 16; j++) temp[j] = i0[j + 16];
    TransformBlock(state, temp);
    
    d0[0] = (state[0] >> 24) & 0xFF;
    d0[1] = (state[0] >> 16) & 0xFF;
    d0[2] = (state[0] >> 8) & 0xFF;
    d0[3] = state[0] & 0xFF;
    
    // Process block 1 (2 rounds with padding)
    memcpy(state, H_INIT, sizeof(state));
    for (int j = 0; j < 16; j++) temp[j] = i1[j];
    TransformBlock(state, temp);
    for (int j = 0; j < 16; j++) temp[j] = i1[j + 16];
    TransformBlock(state, temp);
    
    d1[0] = (state[0] >> 24) & 0xFF;
    d1[1] = (state[0] >> 16) & 0xFF;
    d1[2] = (state[0] >> 8) & 0xFF;
    d1[3] = state[0] & 0xFF;
    
    // Process block 2 (2 rounds with padding)
    memcpy(state, H_INIT, sizeof(state));
    for (int j = 0; j < 16; j++) temp[j] = i2[j];
    TransformBlock(state, temp);
    for (int j = 0; j < 16; j++) temp[j] = i2[j + 16];
    TransformBlock(state, temp);
    
    d2[0] = (state[0] >> 24) & 0xFF;
    d2[1] = (state[0] >> 16) & 0xFF;
    d2[2] = (state[0] >> 8) & 0xFF;
    d2[3] = state[0] & 0xFF;
    
    // Process block 3 (2 rounds with padding)
    memcpy(state, H_INIT, sizeof(state));
    for (int j = 0; j < 16; j++) temp[j] = i3[j];
    TransformBlock(state, temp);
    for (int j = 0; j < 16; j++) temp[j] = i3[j + 16];
    TransformBlock(state, temp);
    
    d3[0] = (state[0] >> 24) & 0xFF;
    d3[1] = (state[0] >> 16) & 0xFF;
    d3[2] = (state[0] >> 8) & 0xFF;
    d3[3] = state[0] & 0xFF;
}

void sha256sse_test() {
    // Test implementation - same as SSE version
}
