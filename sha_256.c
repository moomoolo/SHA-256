//
// Created by henry on 2020/8/27.
//

//
// Created by henry on 2020/8/26.
//

#include "sha_256.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

uint32_t right_rotate(uint32_t x, int k) {
    return (x >> k) + (x << (32 - k));
}

 uint32_t delta_0(uint32_t x) {
    return right_rotate(x, 7) ^ right_rotate(x, 18) ^ (x >> 3);
}

 uint32_t delta_1(uint32_t x) {
    return right_rotate(x, 17) ^ right_rotate(x, 19) ^ (x >> 10);
}

 uint32_t sigma_0(uint32_t x) {
    return right_rotate(x, 2) ^ right_rotate(x, 13) ^ right_rotate(x, 22);
}

 uint32_t sigma_1(uint32_t x) {
    return right_rotate(x, 6) ^ right_rotate(x, 11) ^ right_rotate(x, 25);
}

 uint32_t ch(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (~x & z);
}

 uint32_t maj(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

struct sha_256_value string_to_sha256(uint8_t * mess, uint64_t len) {

    uint32_t H[8] = {
            0x6a09e667,
            0xbb67ae85,
            0x3c6ef372,
            0xa54ff53a,
            0x510e527f,
            0x9b05688c,
            0x1f83d9ab,
            0x5be0cd19
    };
    uint32_t temp[8];
    uint32_t K[64] = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };

    uint32_t W[64];
    uint64_t size_byte = len + 9;
    size_byte = (size_byte + 63) & 0xffffffffffffffc0; //round size_byte to the nearest 64s
    uint8_t * str = (uint8_t * )malloc(size_byte);
    //padding the message;
    memmove(str, mess, len);
    str[len] = 0x80;
    memset(str + len + 1, 0, size_byte - len - 3);
    uint64_t len_bit = len * 8;
    // C is little endian so memmove does not work
    for(int i = 0; i < 8; i++) {
        str[size_byte - i - 1] = len_bit >> (i * 8);
    }

    //sha256 process
    for(int i = 0; i < size_byte; i += 64) {
        memmove(temp, H, sizeof(H));
        for(int j = 0; j < 16; j++) {
            W[j] = 0;
            for(int k = 0; k < 4; k++) {
                W[j] = (W[j] << 8) + str[i + j * 4 + k];
            }
        }
        for(int j = 16; j < 64; j++) {
            W[j] = delta_1(W[j - 2]) + W[j - 7] + delta_0(W[j - 15]) + W[j - 16];
        }
        for(int j = 0; j < 64; j++) {
            uint32_t T1 = temp[7] + sigma_1(temp[4]) + ch(temp[4], temp[5], temp[6]) + K[j] + W[j];
            uint32_t T2 = sigma_0(temp[0]) + maj(temp[0], temp[1], temp[2]);
            memmove(temp + 1, temp, 28);
            temp[4] += T1;
            temp[0] = T1 + T2;
        }
        for(int i = 0; i < 8; i++) {
            H[i] += temp[i];
        }
    }
    free(str);
    struct sha_256_value res;
    memmove(&res, H, sizeof(H));
    return res;
}

