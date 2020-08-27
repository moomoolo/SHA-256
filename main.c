//
// Created by henry on 2020/8/26.
//

#include <stdio.h>
#include <stdint.h>
#include "sha_256.h"
#include <string.h>

int main() {
    printf("Welcome\n");
    char str[10000];
    struct sha_256_value res;
    printf("Input string:");
    gets(str);
    while(strlen(str) != 0) {
        res = string_to_sha256(str, strlen(str));
        printf("Its SHA-256 is:");
        for(int i = 0; i < 8; i++) {
            printf("%x ", res.H[i]);
        }
        printf("\n");
        printf("Input string:");
        gets(str);
    }
    return 0;
}
