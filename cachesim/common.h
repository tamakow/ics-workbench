#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define exp2(x) (1 << (x))
#define mask_with_len(x) (exp2(x) - 1)

#define MEM_SIZE (1 << 25) // 1MB
#define BLOCK_WIDTH  6  // 64B
#define BLOCK_SIZE exp2(BLOCK_WIDTH)

typedef uint8_t bool;
#define true 1
#define false 0

void cycle_increase(int n);

typedef struct{
    bool dirty_bit;
    bool valid_bit;
    uint32_t tag;
    uint32_t data[BLOCK_SIZE];
}cache_line;


#endif
