//
// Created by henry on 2020/8/26.
//

#ifndef SHA_256_SHA_256_H
#define SHA_256_SHA_256_H

#include <stdint.h>

struct sha_256_value
{
    /*
        Hash values of sha_256
    */
    uint32_t H[8];
};

 uint32_t right_rotate(uint32_t x, int k);

 uint32_t delta_0(uint32_t x);

 uint32_t delta_1(uint32_t x);

 uint32_t sigma_0(uint32_t x);

 uint32_t sigma_1(uint32_t x);

 uint32_t ch(uint32_t x, uint32_t y, uint32_t z);


 uint32_t maj(uint32_t x, uint32_t y, uint32_t z);

struct sha_256_value string_to_sha256(uint8_t *str, uint64_t len);

#undef SHAR_256_H

#endif //SHA_256_SHA_256_H
